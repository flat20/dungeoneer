
#include <stdio.h>
#include <dungeoneer_mod.h>
#include <queue>
#include <functional>
#include <mutex>

#include "debug.h"
#include "ui.h"

ModuleInfo modInfo = {
    DUNGEONEER_VERSION,
    "Debug",
    &Draw,
};

//void UObject_ProcessEvent(UObject* object, UFunction* func, void *params);

//UIData uiData;

//tUObject_ProcessEvent origUObject_ProcessEvent;
std::queue<debug::CommandExecutor> commandQueue;
std::mutex commandQueueMtx;
typedef IModuleInterface* ( *FInitializeModuleFunctionPtr )( void );
// Called when Mod gets loaded
void ModMain(Dungeoneer *dng, Module *mod) {

    // origUObject_ProcessEvent = (tUObject_ProcessEvent)dng->spyData->functionPtrs[RefUObject_ProcessEvent];
    // dng->AddFunctionHandler(mod, RefUObject_ProcessEvent, &UObject_ProcessEvent);

    printf("debug does nothing right now\n");

    // auto GetDllHandle = (tFWindowsPlatformProcess_GetDllHandle)dng->spyData->functionPtrs[RefFWindowsPlatformProcess_GetDllHandle];
    // void* handle = GetDllHandle((TCHAR*)L"UE4Editor-MyMod.dll");
    // printf("tried loading %llx\n", (uintptr_t)handle);
    // if (handle == nullptr) {
    //     return;
    // }

    // FInitializeModuleFunctionPtr initFuncPtr = (FInitializeModuleFunctionPtr)GetProcAddress((HMODULE)handle, "InitializeModule");
    // printf("func ptr %llx\n", (uintptr_t)initFuncPtr);
    // if (initFuncPtr == nullptr) {
    //     return;
    // }

    // IModuleInterface *module = initFuncPtr();
    // printf("init module %llx\n", (uintptr_t)module);
    // module->StartupModule();
    // printf("startup called\n");
    // printf("isgameModule %s\n", module->IsGameModule() ? "true" : "false");
    

    // FInitializeModuleFunctionPtr InitializeModuleFunctionPtr =
    //     (FInitializeModuleFunctionPtr)FPlatformProcess::GetDllExport(ModuleInfo->Handle, TEXT("InitializeModule"));
    //     // Initialize the module!
	// 					ModuleInfo->Module = TUniquePtr<IModuleInterface>(InitializeModuleFunctionPtr());
    //             ModuleInfo->Module->StartupModule();
    //             ModulesChangedEvent.Broadcast(InModuleName, EModuleChangeReason::ModuleLoaded);

}

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params) {
   std::lock_guard<std::mutex> lck(commandQueueMtx);
   if (commandQueue.empty()) {
       return;
   }
   debug::CommandExecutor fn = commandQueue.front();
   commandQueue.pop();
   fn(true);
}


void debug::AddExecutor(CommandExecutor fn) {
    std::lock_guard<std::mutex> lck(commandQueueMtx);
    commandQueue.push(fn);
}

std::vector<UObject*> debug::Search(const char *obj, const char *cls) {
    if (strlen(obj) == 0) {
        obj = nullptr;
    }
    if (strlen(cls) == 0) {
        cls = nullptr;
    }
    std::vector<UObject *> found;
    for (spy::FRawObjectIterator It(false); It; ++It) {
        UObject *Object = *It;
        // if objectName is requested but doesn't match, continue
        if (obj != nullptr && strstr(spy::GetName(Object), obj) == nullptr) {
            continue;
        }

        // if className is requested but doesn't match, continue
        if (cls != nullptr && strstr(spy::GetName(Object->GetClass()), cls) == nullptr) {
            continue;
        }

        printf("  %s (%s) %llx\n", spy::GetName(Object), spy::GetName(Object->GetClass()), (uintptr_t)Object);
        found.push_back(Object);

    }
    printf("done\n");
    return found;

}

std::vector<UObjectData> debug::ListProperties(UObject *Object) {

    std::vector<UObjectData> found;
    for (TFieldIterator<UObject> it(Object->GetClass()); it; ++it) {
        UObject *f = *it;
        std::string clsName = (f != nullptr) ? spy::GetName(f->GetClass()) : nullptr;
        found.push_back(UObjectData{f, nullptr, spy::GetName(f), clsName});
    }
    return found;

}