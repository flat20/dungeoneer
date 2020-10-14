#include <windows.h>
#include <Psapi.h>
#include <map>
#include "unrealspy.h"
#include "util.h"
#include "offsets.h"
#include "console.h"

#include <MinHook.h>



namespace spy {
    Data data = {};
}


// __int64 __fastcall subAddEmeraldsDelegateListener(__int64 a1, __int64 a2)
// typedef void* (__thiscall *tAddEmeralds) (void *a1, void *a2);
// void* AddEmeralds(void *, void *);

// a1 should be this. and a2 should be a TArray of arguments? or something. Suppose it depends
// on what function type was added as a listener.
// void* AddEmeralds(void *a1, void *a2) {

//     // a1 is a TArray, Num matches number of arguments.
//     auto args = (TArray<void *>*)a1;
//     printf("args %d\n", args->ArrayNum);
//     for (int i=0; i<args->ArrayNum; i++) {
//         hexDump(args->Data, 64);
//     }

//     printf("a1 %llx\n", (uintptr_t)a1);
//     hexDump(a1, 32);
//     printf("at a1's first pointer\n");
//     hexDump(*(void**)a1, 32);
//     printf("a2 %llx\n", (uintptr_t)a2);
//     hexDump(a2, 32);
//     void *result = ((tAddEmeralds)spy::spyData->hooks[RefAddEmeralds]->original)(a1, a2);

//     return result;
// }

// We shouldn't force a user into our basic API. Leaving some options
bool SetHook(LPVOID target, const void *detour, LPVOID *original);
// Address to target and address to our hook
bool SetHook(spy::Hook *hook);
bool EnableHook(uintptr_t address);
bool RemoveHook(spy::Hook *hook);

// Address to target and address to our hook
bool SetHook(LPVOID target, const void* detour, LPVOID* original) {

    MH_STATUS err;

    err = MH_CreateHook(target, (LPVOID)detour, original);
    if (err != MH_OK) {
        printf("MH_CreateHook failed: %d\n", err);
        return false;
    }

    return true;
}


// Address to target and address to our hook
bool SetHook(spy::Hook *hook) {

    LPVOID target = (LPVOID)(hook->address);

    return SetHook(target, hook->detour, &hook->original);
}

bool RemoveHook(spy::Hook *hook) {
    if (hook->address == 0) {
        return false;
    }
    if (MH_DisableHook((LPVOID)hook->address) != MH_OK) {
        return false;
    }
    return true;
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



spy::Data *spy::Init(std::function<void (Data *spyData)> fnInitialized, std::map<UE4Reference, std::string> functionPatterns) {

    // Get our DLL's base address
    HMODULE dll = GetModuleHandle(NULL);
    uintptr_t baseAddress = (uintptr_t)dll;
    data.baseAddress = baseAddress;

    HANDLE process = GetCurrentProcess();
    data.functionPtrs = offsets::FindAddresses(process, functionPatterns); // offsets::defaultAddressLookups

    // TODO Separate thread and loop until we have them or have to give up.

        // We can get GNames by calling FName::GetNames()
        //FName_GetNames GetNames = (FName_GetNames)data.functionPtrs[RefFName_GetNames];
        data.GNames = GetFunction<tFName_GetNames>(RefFName_GetNames)();

        // We can get GUObjectArray by instantiating FRawObjectIterator. It just so happens that it
        // holds a reference to GUObjectArray.
        char bla[256];
        auto objectIteratorCtor = (tFRawObjectIterator_Ctor)data.functionPtrs[RefFRawObjectIterator_Ctor];
        void **ref = (void**)objectIteratorCtor(&bla[0], false);
        data.GUObjectArray = (FUObjectArray*)*ref;

        // Setup util functions
        util::GNames = data.GNames;
        util::GUObjectArray = data.GUObjectArray;


        UObject *engine = util::FindObjectByName("GameEngine", "GameEngine");
        data.GEngine = (UEngine*)engine;

        printf("initspy gengine? %s\n", util::getName(data.GEngine));


    // Hook functions
    if (MH_Initialize() != MH_OK) {
        printf("MH_Initialize failed\n");
        return false;
    }

    fnInitialized(&data);

    return &data;
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


// We need the original set immediately or our detour
// could get called without having an original function to call
bool spy::HookFunctionRef(UE4Reference refName, const void *detour, void **original) {
    
    // Already have it
    if (data.hooks.count(refName) > 0) {
        return false;
    }

    Hook *hook = new Hook{GetFunctionRef(refName), detour};
    bool result = SetHook(hook);
    if (result == false) {
        return false;
    }

    // Update original if it's wanted.
    // Can still be found in data.hooks[]->original
    if (original != nullptr) {
        *original = hook->original;
    }

    result = EnableHook(hook->address);
    if (result == false) {
        delete hook;
        return false;
    }

    data.hooks[refName] = hook;

    return true;
}

bool spy::UnhookFunctionRef(UE4Reference refName) {
    
    // Don't have it
    if (data.hooks.count(refName) == 0) {
        return false;
    }

    Hook *hook = data.hooks[refName];
    bool result = RemoveHook(hook);

    // Delete regardless of removal result. Maybe?
    delete hook;
    data.hooks.erase(refName);

    return result;
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