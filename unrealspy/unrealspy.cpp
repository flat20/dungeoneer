#include <windows.h>
#include <Psapi.h>
#include <map>
#include "unrealspy.h"
//#include "unreal_util.h"
#include "util.h"

#include <MinHook.h>



struct Hook {
    uintptr_t address;
    void *detour;   // Point this to function
    LPVOID original; // Pointer so we can call the original implementation of the function. Returned after hooking
};

// struct Offset {
//     uint64 offset;
//     void *ptr;      // Pointer to location in running process, once the Offset has been looked up.
// };

// We shouldn't force a user into our basic API. Leaving some options
bool SetHook(LPVOID target, LPVOID detour, LPVOID* original);
// Address to target and address to our hook
bool SetHook(Hook *hook);
bool EnableHook(uintptr_t address);





// Offsets to functions. Name each entry?
std::map<UE4Reference, Hook*> hooks;
//std::map<UE4Reference, Offset*> offsets; // Rename to variables? or references?

// Call from within the UE game process
// Sets up GNames global for the util:: namespace to work
bool InitSpy(SpyData *data, std::map<UE4Reference, uintptr_t> addresses) {

    // We end up with the same base address as the one we're injected in
    HMODULE dll = GetModuleHandle(NULL);
    uint64 baseAddress = (uint64)dll;
    //HMODULE baseAddress = GetModuleHandleA("Dungeons-Win64-Shipping.exe");
    data->baseAddress = baseAddress;

    uintptr_t offsAddEmeralds = 0x3DFEE90;
    uintptr_t addrAddEmerals = baseAddress + offsAddEmeralds;
    printf("addrAddEmerals %llx\n", addrAddEmerals);
    printf("addrLevelStart %llx\n", baseAddress + 0x3DFEEB0);
    
    //addresses[RefFConsoleManager_ForEachConsoleObjectThatContains];


    data->AHUD_DrawRect = (AHUD_DrawRect)addresses["AHUD_DrawRect"];
    data->AHUD_DrawText = (AHUD_DrawText)addresses["AHUD_DrawText"];
    data->AHUD_GetTextSize = (AHUD_GetTextSize)addresses["AHUD_GetTextSize"];
    data->StaticLoadObject = (StaticLoadObject)addresses[RefStaticLoadObject];
    data->StaticLoadClass = (StaticLoadClass)addresses[RefStaticLoadClass];
    data->LoadPackage = (LoadPackage)addresses[RefLoadPackage];
    data->FName_GetNames = (FName_GetNames)addresses[RefFName_GetNames];
    data->FRawObjectIterator_Ctor = (FRawObjectIterator_Ctor)addresses[RefFRawObjectIterator_Ctor];
    data->StaticConstructObject_Internal = (StaticConstructObject_Internal)addresses[RefStaticConstructObject_Internal];

    // We can get GNames by calling FName::GetNames()
    data->GNames = data->FName_GetNames();
    util::GNames = data->GNames;

    // We can get GUObjectArray by instantiating FRawObjectIterator. It happens that it
    // holds a reference to GUObjectArray.
    char bla[256];
    void **ref = (void**)data->FRawObjectIterator_Ctor(&bla[0], false);
    data->GUObjectArray = (FUObjectArray*)*ref;
    util::GUObjectArray = data->GUObjectArray;

    printf("guobjectarray: %llx\n", (uint64)data->GUObjectArray);
    printf("  NumElements %d\n", data->GUObjectArray->ObjObjects.NumElements);
    printf("  NumElementsPerChunk %d\n", data->GUObjectArray->ObjObjects.NumElementsPerChunk);
    printf("  NumChunks %d\n", data->GUObjectArray->ObjObjects.NumChunks);
    printf("  MaxChunks %d\n", data->GUObjectArray->ObjObjects.MaxChunks);
    printf("  MaxElements %d\n", data->GUObjectArray->ObjObjects.MaxElements);

    UObject *engine = util::FindObjectByName("GameEngine", "GameEngine");
    data->GEngine = (UEngine*)engine;

    UClass *ConsoleClass = util::GetPropertyValueByPath<UClass>(data->GEngine, data->GEngine, "ConsoleClass");
    printf("consoleclass? %llx\n", (uint64)ConsoleClass);
    if (ConsoleClass != nullptr) {
        printf("%s\n", util::getName(ConsoleClass));
    }

    hooks[RefUObject_ProcessEvent]  = new Hook{addresses[RefUObject_ProcessEvent],    data->detourProcessEvent};
    hooks[RefAActor_ProcessEvent]  = new Hook{addresses[RefAActor_ProcessEvent],    data->detourAActor_ProcessEvent};
    hooks[RefAHUD_PostRender]       = new Hook{addresses[RefAHUD_PostRender],   data->detourPostRender};
    hooks[RefFConsoleManager_ProcessUserConsoleInput] = new Hook{addresses[RefFConsoleManager_ProcessUserConsoleInput],   data->detourProcessUserConsoleInput};

    // Hook functions
    if (MH_Initialize() != MH_OK) {
        printf("MH_Initialize failed\n");
        return false;
    }

    for(const auto &v: hooks) {
        std::string label = v.first;
        Hook *hook = v.second;
        if (hook->detour == nullptr) {
            continue;
        }

        bool success = SetHook(hook);
        if (success == false) {
            printf("%s hook not set\n", label.c_str());
            return false;
        }
    }

    data->origProcessEvent = (tProcessEvent)hooks[RefUObject_ProcessEvent]->original;
    data->origAActor_ProcessEvent = (tAActor_ProcessEvent)hooks[RefAActor_ProcessEvent]->original;
    data->origPostRender = (tPostRender)hooks[RefAHUD_PostRender]->original;
    data->origProcessUserConsoleInput = (tFConsoleManager_ProcessUserConsoleInput)hooks[RefFConsoleManager_ProcessUserConsoleInput]->original;
    
    //data->origGetNames = (tGetNames)hooks["GetNames"]->original;

    // Enable hooks once we have pointers to original functions
    for(const auto &v: hooks) {
        std::string label = v.first;
        Hook *hook = v.second;
        if (hook->detour == nullptr) {
            continue;
        }
        bool success = EnableHook(hook->address);
        if (success == false) {
            printf("%s hook not enabled\n", label.c_str());
            return false;
        }
    }
    return true;
}


bool DeInitSpy(SpyData *data) {

    // Disable hooks
    HMODULE dll = GetModuleHandle(NULL);
    uint64 baseAddress = (uint64)dll;

    // if (data->detourProcessEvent != nullptr) {
    //     if (MH_DisableHook((LPVOID)(baseAddress + ofsUObject_ProcessEvent)) != MH_OK) {
    //         return false;
    //     }
    // }

    // if (data->detourPostRender != nullptr) {
    //     if (MH_DisableHook((LPVOID)(baseAddress + ofsAHUD_PostRender)) != MH_OK) {
    //         return false;
    //     }
    // }

    // Uninitialize MinHook.
    if (MH_Uninitialize() != MH_OK) {
        return false;
    }
    return true;
}

// Address to target and address to our hook
bool SetHook(LPVOID target, LPVOID detour, LPVOID* original) {
    //LPVOID original = nullptr;
    MH_STATUS err;

    err = MH_CreateHook(target, detour, original);
    if (err != MH_OK) {
        printf("MH_CreateHook failed: %d\n", err);
        return false;
    }

    // err = MH_EnableHook(target);
    // if (err != MH_OK) {
    //     printf("MH_EnableHook failed: %d\n", err);
    //     return false;
    // }
    return true;
}


// Address to target and address to our hook
bool SetHook(Hook *hook) {

    LPVOID target = (LPVOID)(hook->address);

    return SetHook(target, hook->detour, &hook->original);
}

bool EnableHook(uintptr_t address) {
    LPVOID target = (LPVOID)(address);
    MH_STATUS err = MH_EnableHook(target);
    if (err != MH_OK) {
        printf("MH_EnableHook failed: %d\n", err);
        return false;
    }
    return true;
}
