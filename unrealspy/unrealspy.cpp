#include <map>
#include <thread>
#include "unrealspy.h"
//#include "util.h"
#include "offsets.h"
#include "console.h"

#include <windows.h>
#include <Psapi.h>

#include <MinHook.h>

// From UnrealMath.cpp
// TODO This is diet-ue stuff
CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);

namespace spy {
    Data data = {};
}


	bool GetName(UObject *obj, ANSICHAR (&OutName)[1024]) {
		FName name = obj->GetFName();
		TNameEntryArray& Names = *spy::data.GNames;

		// Code from the ue source.
		const NAME_INDEX Index = name.GetDisplayIndex();
		const FNameEntry* const NameEntry = Names[Index];

		// GetComparisonIndex() seems to be the same thing as display index?

		NameEntry->GetAnsiName(OutName);
        return true;
	}

	ANSICHAR *GetName(UObject *obj) {
		FName name = obj->GetFName();
		TNameEntryArray& Names = *spy::data.GNames;

		// Code from the ue source.
		const NAME_INDEX Index = name.GetDisplayIndex();

        diet::FNameEntry *ne = (diet::FNameEntry*)Names[Index];
        return (ANSICHAR*)ne->GetPtr();
		// GetComparisonIndex() seems to be the same thing as display index?

	}

	UObject *FindObjectByName(char *ObjectName, char *ClassName) {
        for (diet::FRawObjectIterator It(*spy::data.GUObjectArray); It; ++It) {

            FUObjectItem *item = *It;
            UObject *obj = (UObject*)item->Object;

            // if objectName is requested but doesn't match, continue
            if (ObjectName != nullptr && strcmp(GetName(obj), ObjectName) != 0) {
                continue;
            }

            // if className is requested but doesn't match, continue
            if (ClassName != nullptr && strcmp(GetName(obj->GetClass()), ClassName) != 0) {
                continue;
            }

            return obj;
        }
        return nullptr;
	}

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

    // // Attempt to find the vars for 60 seconds before giving up
    for (int i=0; i<30; i++) {

        bool success = initVars();
        if (success == true) {
            return &data;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
        // We can get GNames by calling FName::GetNames()
        //FName_GetNames GetNames = (FName_GetNames)data.functionPtrs[RefFName_GetNames];
        // if (data.GNames == nullptr) {
        //     data.GNames = GetFunction<tFName_GetNames>(RefFName_GetNames)();
            
        //     util::GNames = data.GNames;
        // }
    // }
    //     // We can get GUObjectArray by instantiating FRawObjectIterator. It just so happens that it
    //     // holds a reference to GUObjectArray.
    //     if (data.GUObjectArray == nullptr) {
    //         char bla[256];
    //         auto objectIteratorCtor = (tFRawObjectIterator_Ctor)data.functionPtrs[RefFRawObjectIterator_Ctor];
    //         void **ref = (void**)objectIteratorCtor(&bla[0], false);
    //         data.GUObjectArray = (FUObjectArray*)*ref;
    //         util::GUObjectArray = data.GUObjectArray;
    //     }

    //     // Check for GEngine and also make sure there's a GameViewport assigned
    //     // so console works.
    //     if (data.GEngine == nullptr && util::GNames != nullptr && util::GUObjectArray != nullptr) {
    //         UObject *engine = util::FindObjectByName("GameEngine", "GameEngine");

    //         UObject *GameViewport = util::GetPropertyValueByPath<UObject>(engine, engine, "GameViewport");
    //         if (GameViewport != nullptr) {
    //             data.GEngine = (UEngine*)engine;
    //         }
    //     }

    //     if (data.GNames != nullptr && data.GUObjectArray != nullptr && data.GEngine != nullptr) {

    //         // Hook functions
    //         if (MH_Initialize() != MH_OK) {
    //             printf("MH_Initialize failed. No hooking will work\n");
    //             return nullptr;
    //         }

    //         return &data;
    //     }

    //     std::this_thread::sleep_for(std::chrono::seconds(2));

    // }

    // printf("Failed to find the UE4 variables after 60 seconds :(\n");
    // printf("GNames: %llx\n", (uintptr_t)data.GNames);
    // printf("GUObjectArray: %llx\n", (uintptr_t)data.GUObjectArray);
    // printf("GEngine: %llx\n", (uintptr_t)data.GEngine);

    return nullptr;
}

bool spy::initVars() {
//     // We can get GNames by calling FName::GetNames()
//     //FName_GetNames GetNames = (FName_GetNames)data.functionPtrs[RefFName_GetNames];

    if (data.GNames == nullptr) {
        TNameEntryArray& names = GetFunction<tFName_GetNames>(RefFName_GetNames)();
        data.GNames = &names;

        auto e = names[1];

        ANSICHAR OutName[1024];
        e->GetAnsiName(OutName);
        printf("ok? %d %s\n", e->GetIndex(), OutName);

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
            printf("GEngine found.\n");
        }
//         FUObjectArray::TIterator *it = new FUObjectArray::TIterator(*data.GUObjectArray);
//         UObject *engine = util::FindObjectByName("GameEngine", "GameEngine");
//         data.GEngine = (UEngine*)engine;
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