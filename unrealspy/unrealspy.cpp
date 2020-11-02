#include <map>
#include <thread>
#include "unrealspy.h"
//#include "util.h"
#include "helpers.h"
#include "offsets.h"
#include "console.h"
#include "uhook.h"

#include <windows.h>
#include <Psapi.h>


// From UnrealMath.cpp
// TODO This is diet-ue stuff
CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);

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
        printf("%s = %llx\n", it.first.c_str(), it.second);
    }

    if (data.functionPtrs[RefFName_GetNames] == 0) {
        printf("No FName::GetNames()\n");
        return nullptr;
    }

    if (data.functionPtrs[RefFRawObjectIterator_Ctor] == 0) {
        printf("No RawObjectIterator()\n");
        return nullptr;
    }

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

    if (data.GNames == nullptr) {
        TNameEntryArray& names = GetFunction<tFName_GetNames>(RefFName_GetNames)();
        data.GNames = &names;

//         util::GNames = data.GNames;
    }

//     // We can get GUObjectArray by instantiating FRawObjectIterator. It just so happens that it
//     // holds a reference to GUObjectArray as its first member
    if (data.GUObjectArray == nullptr) {
        char bla[256];
        auto objectIteratorCtor = (tFRawObjectIterator_Ctor)data.functionPtrs[RefFRawObjectIterator_Ctor];
        void **ref = (void**)objectIteratorCtor(&bla[0], false);

        data.GUObjectArray = (FUObjectArray*)*ref;

//        printf("global set? %s\n", GUObjectArray.IsOpenForDisregardForGC() ? "true" : "false");
        
//        auto e = data.GNames[name.GetIndex()];

//        util::GUObjectArray = data.GUObjectArray;
    }

    if (data.GEngine == nullptr && data.GUObjectArray != nullptr && data.GNames != nullptr) {

        // TNameEntryArray& Names = *data.GNames;
        // Names[EName::NAME_Engine];

        UObject *engine = FindObjectByName("GameEngine", "GameEngine");
        if (engine != nullptr) {
            data.GEngine = (UEngine*)engine;
        }

    }

    // Still haven't got all variables
    if (data.GNames == nullptr || data.GUObjectArray == nullptr) {// || data.GEngine == nullptr) {
        return false;
    }
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