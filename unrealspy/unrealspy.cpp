#include <map>
#include <thread>
#include "unrealspy.h"
#include <helpers.h>
#include "offsets.h"
#include "console.h"
#include "uhook.h"

#include <windows.h>
#include <Psapi.h>
#include <iostream>
#include <iomanip>

template <class T>
void hexDumpValue(const unsigned char * p, unsigned int offset) {
    const int width = sizeof(T)*2; // 16, times two for hex
    const T * valuePtr = reinterpret_cast< const T *>( p+offset );
    for (int i=0; i<16; i+=sizeof(T)) {
        //std::cout << "  =" << std::setw(width) << std::setfill( ' ' ) << *valuePtr;
        std::cout << "  =" << *valuePtr;
        valuePtr++;
    }
}

void hexDump16Bytes(const unsigned char * p, unsigned int offset) {
    
    // address and offset
    std::cout << std::setw(12) << std::setfill( '0' ) << std::hex << (uint64_t)p+offset;
    std::cout << "  ";
    std::cout << std::setw(4) << offset;
    std::cout << "  ";

    unsigned int n = 16;
    for ( unsigned int i = 0; i < n; i++ ) {
        if (i % 8 == 0) {   // space
            std::cout << "  ";
        }
        
        std::cout << std::setw(2) << std::setfill( '0' ) << std::hex << int(p[offset+i]) << " ";
    }

    hexDumpValue<uint64_t>(p, offset);
    //hexDumpValue<float>(p, offset);

    std::cout << std::endl;
}

void hexDump(const void * mem, unsigned int n) {
    const unsigned char * p = reinterpret_cast< const unsigned char *>( mem );
    for ( unsigned int i = 0; i < n; i+=16 ) {
        hexDump16Bytes(p, i);
    }
}

namespace spy {
    Data data = {};
}



// Can block for up to 60 seconds while getting the needed variables.
// Run in a separate thread if that's a problem.
spy::Data *spy::Init(std::map<UE4Reference, std::string> functionPatterns) {

    // Get our DLL's base address
    HMODULE dll = GetModuleHandle(NULL);
    uintptr_t baseAddress = (uintptr_t)dll;
    data.baseAddress = baseAddress;

    HANDLE process = GetCurrentProcess();
    data.functionPtrs = offsets::FindAddresses(process, functionPatterns); // offsets::defaultAddressLookups
    for(auto &it : data.functionPtrs) {
        printf("%s = %I64x\n", it.first.c_str(), (uintptr_t)it.second);
    }

    // if (data.functionPtrs[RefFName_GetNames] == 0) {
    //     printf("No FName::GetNames()\n");
    //     return nullptr;
    // }

    // if (data.functionPtrs[RefFRawObjectIterator_Ctor] == 0) {
    //     printf("No RawObjectIterator()\n");
    //     return nullptr;
    // }

    // Should be optional
    InitHook();

    // // Attempt to find the vars for 60 seconds before giving up
    for (int i=0; i<30; i++) {

        bool success = initVars();
        if (success == true) {
            return &data;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return nullptr;
}


bool spy::initVars() {

//     // We can get GNames by calling FName::GetNames()
//     //FName_GetNames GetNames = (FName_GetNames)data.functionPtrs[RefFName_GetNames];
#ifdef UE_422
    if (GNames == nullptr) {
        TNameEntryArray& names = GetFunction<tFName_GetNames>(RefFName_GetNames)();
        spy::GNames = &names;
    }

//     // We can get GUObjectArray by instantiating FRawObjectIterator. It just so happens that it
//     // holds a reference to GUObjectArray as its first member
    if (spy::GUObjectArray == nullptr) {
        char bla[256];
        auto objectIteratorCtor = (tFRawObjectIterator_Ctor)data.functionPtrs[RefFRawObjectIterator_Ctor];
        void **ref = (void**)objectIteratorCtor(&bla[0], false);
        spy::GUObjectArray = (FUObjectArray*)*ref;
    }

    // When we have names and objects, get uengine
    if (spy::GEngine == nullptr && spy::GUObjectArray != nullptr && spy::GNames != nullptr) {

        UObject *engine = FindObjectByName("GameEngine", "GameEngine");
        if (engine != nullptr) {
            spy::GEngine = (UEngine*)engine;
        }

    }

    // Still haven't got all variables
    if (spy::GNames == nullptr || spy::GUObjectArray == nullptr || spy::GEngine == nullptr) {
        return false;
    }
#else

    if (spy::GUObjectArray == nullptr) {
        // Passing in a fake UClass to satisfy the code and make it not crash.
        char bla[256];
        auto objectIteratorCtor = (tFObjectIterator_Ctor)data.functionPtrs[RefFObjectIterator_Ctor];
        void **ref = (void**)objectIteratorCtor(&bla[0], (UClass*)&bla[0], false, EObjectFlags::RF_NoFlags, EInternalObjectFlags::None);
        spy::GUObjectArray = (FUObjectArray*)*ref;
    }

    // When we have objects, get uengine
    if (spy::GEngine == nullptr && spy::GUObjectArray != nullptr) {

        //00007FF7BE524F90 - 00007FF7BA8E0000 = 3C44F90
        // MATCH! GameEngine_2147482615
        //        GameEngine_2147482615
        // StaticConstructObject_Internal = 0

        UEngine *actual = *(UEngine**)(data.baseAddress + (uintptr_t)0x3C44F90);
        printf("actual? %llx\n", (uintptr_t)actual);
        UObject *engine = FindObjectByName(nullptr, L"GameEngine", L"/Engine/Transient");
        printf("engine? %llx\n", (uintptr_t)engine);
        if (engine != nullptr) {
            spy::GEngine = (UEngine*)engine;

            // for (spy::FRawObjectIterator It(false); It; ++It) {

            //     UObject *obj = *It;
            //     if (wcscmp(GetName(obj->GetClass()), L"GameEngine") == 0 && wcscmp(GetName(obj->GetOuter()), L"/Engine/Transient")) {
            //         printf("this one?\n");
            //         printf(" %ws\n", GetName(obj->GetClass()));
            //         printf(" %ws\n", GetName(obj->GetOuter()));
            //     }
            //     if ((uintptr_t)obj == (uintptr_t)actual) {
            //         printf("MATCH! %ws\n", GetName(obj));
            //         printf(" %ws\n", GetName(obj->GetClass()));
            //         printf(" %ws\n", GetName(obj->GetOuter()));
            //         // printf(" %ws\n", GetName(obj->GetClass()->GetSuperClass()));
            //         break;
            //     }
            // }
        }

    }

    // Still haven't got all variables
    if (spy::GUObjectArray == nullptr || spy::GEngine == nullptr) {
        return false;
    }
#endif
    return true;
}

uintptr_t spy::AddFunctionRef(UE4Reference refName, std::string pattern) {

    // Already have it
    if (data.functionPtrs.count(refName) > 0) {
        return data.functionPtrs[refName];
    }

    // TODO Refactor offset namespace
    std::map<UE4Reference,std::string> functionPatterns = {{refName, pattern}};

    HANDLE process = GetCurrentProcess();
    std::map<UE4Reference,uintptr_t> addresses = offsets::FindAddresses(process, functionPatterns);

    data.functionPtrs[refName] = addresses[refName];

    return addresses[refName];
}

uintptr_t spy::GetFunctionRef(UE4Reference refName) {
    return data.functionPtrs[refName];
}


// bool DeInitSpy(SpyData *data) {

//     // Disable hooks
//     HMODULE dll = GetModuleHandle(NULL);
//     uint64 baseAddress = (uint64)dll;

//     // if (data->detourProcessEvent != nullptr) {
//     //     if (MH_DisableHook((LPVOID)(baseAddress + ofsUObject_ProcessEvent)) != MH_OK) {
//     //         return false;
//     //     }
//     // }

//     // if (data->detourPostRender != nullptr) {
//     //     if (MH_DisableHook((LPVOID)(baseAddress + ofsAHUD_PostRender)) != MH_OK) {
//     //         return false;
//     //     }
//     // }

//     // Uninitialize MinHook.
//     if (MH_Uninitialize() != MH_OK) {
//         return false;
//     }
//     return true;
// }