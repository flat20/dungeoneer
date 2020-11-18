#include <map>
#include <thread>
#include "unrealspy.h"
#include <helpers.h>
#include "offsets.h"
#include "functions.h"
#include "console.h"
#include "uhook.h"

#include <windows.h>
#include <Psapi.h>
#include <iostream>
#include <iomanip>

// Can this go inside functions.h as well?
namespace spy {
    std::vector<offsets::OpcodeAddress*> defaultFunctionLookups = {
        &functions::FName_GetNames,
        &functions::FRawObjectIterator,
        &functions::StaticConstructObject_Internal,
        &functions::UConsole_ConsoleCommand,
    };
}

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
spy::Data *spy::Init(std::vector<offsets::OpcodeAddress*> functionLookups) {

    // Get our DLL's base address
    HMODULE dll = GetModuleHandle(NULL);
    uintptr_t baseAddress = (uintptr_t)dll;
    data.baseAddress = baseAddress;
    HANDLE process = GetCurrentProcess();

    offsets::FindAddresses(process, functionLookups); // offsets::defaultAddressLookups
    bool lookupSuccess = true;
    for (auto opcode : functionLookups) {
        printf("opcode lookup %llx = %s\n", opcode->GetAddress(), opcode->GetOpcodes());
        if (opcode->GetAddress() == 0) {
            lookupSuccess = false;
        }
    }
    printf("address for getnames: %llx\n", functions::FName_GetNames.GetAddress());

    if (lookupSuccess == false) {
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

// uintptr_t spy::AddFunctionRef(UE4Reference refName, std::string pattern) {

//     // Already have it
//     if (data.functionPtrs.count(refName) > 0) {
//         return data.functionPtrs[refName];
//     }

//     // TODO Refactor offset namespace
//     std::map<UE4Reference,std::string> functionPatterns = {{refName, pattern}};

//     HANDLE process = GetCurrentProcess();
//     std::map<UE4Reference,uintptr_t> addresses = offsets::FindAddresses(process, functionPatterns);

//     data.functionPtrs[refName] = addresses[refName];

//     return addresses[refName];
// }

// uintptr_t spy::GetFunctionRef(UE4Reference refName) {
//     return data.functionPtrs[refName];
// }


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