#include <Windows.h>
#include <stdio.h>
#include <list>
#include <map>
#include <mutex>

#include <unrealspy.h>
#include <offsets.h>
#include <util.h>
#include <console.h>

#include "dungeoneer.h"
#include "ui.h"


signed int __stdcall UObject_ProcessEvent(UObject* object, UFunction* func, void* params);
signed int __stdcall AActor_ProcessEvent(AActor* thisActor, UFunction* func, void* params);
void __stdcall AHUD_PostRender(void* hud);
//void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);
void* __stdcall GetNames();

HMODULE loadMod(LPCSTR filename);
std::string getDllDirectory();

// TODO Maybe in Dungeoneer data
std::string dllDirectory;

// Global function handlers for all mods.
std::map<FunctionName,std::list<void *>> functionHandlers;

// Lookup for loaded modules.
std::map<std::string,Module*> loadedModules;

void onLoadPressed(const char *);
void onUnloadPressed(const char *);
void ClearPostRenderHandlers();
void ClearProcessEventHandlers();
std::vector<std::string> listMods(std::string directory);


//bool InitConsole();

// std::list<void *> processEventHandlers;
// std::mutex processEventHandlersMutex;
// std::list<tPostRender> postRenderHandlers;
// std::mutex postRenderHandlersMutex;

Dungeoneer dng;
SpyData spyData;
UIData uiData;

using namespace util;

void __stdcall AddFunctionHandler(Module *mod, FunctionName funcName, void *fnHandler) {
    mod->functionHandlers[funcName] = fnHandler;

    functionHandlers[funcName].push_back(fnHandler);

    // printf("dll.cpp functionHandlers size %zd\n", functionHandlers.size());
    // printf("mod functionHandlers size %zd\n", mod->functionHandlers.size());
    // // Eventually get rid of this
    // if (funcName.compare("UObject_ProcessEvent")) {
    //     AddProcessEventHandler(handler);
    // } else if (funcName.compare("AHUD_PostRender")) {
    //     AddPostRenderHandler((tPostRender)handler->fnHandler);
    // }

}

void RemoveFunctionHandler(Module *mod, FunctionName funcName, void *fnHandler) {
    mod->functionHandlers.erase(funcName);
    
    functionHandlers[funcName].remove(fnHandler);
}

void ClearFunctionHandlers(Module *mod) {
    // 
    for (auto &it = mod->functionHandlers.begin(); it !=  mod->functionHandlers.end(); it++) {
        FunctionName funcName = it->first;
        void *fnHandler = it->second;
        functionHandlers[funcName].remove(fnHandler);
        if (functionHandlers[funcName].size() == 0) {
            functionHandlers.erase(funcName);
        }
//            RemoveFunctionHandler(funcName, fnHandler);
//            functionHandlers.erase(funcName);
    }

    mod->functionHandlers.clear();

    // printf("dll.cpp functionHandlers size %zd\n", functionHandlers.size());
    // printf("mod functionHandlers size %zd\n", mod->functionHandlers.size());
    // ClearPostRenderHandlers();
    // ClearProcessEventHandlers();

}




BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {

    if (dwReason == DLL_PROCESS_ATTACH) {

        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

        // Any extra addresses to lookup
        std::map<UE4Reference,uintptr_t> addresses;

        // TODO InitSpy(.., hookListeners[RefUObject_ProcessEvent] = &UObject_ProcessEvent)
        spyData.detourProcessEvent = &UObject_ProcessEvent;
        spyData.detourAActor_ProcessEvent = &AActor_ProcessEvent;
        spyData.detourPostRender = &AHUD_PostRender;
        InitSpy(&spyData, addresses);

        dng.spyData = &spyData;
        dng.AddFunctionHandler = &AddFunctionHandler;

        // Some ui vars
        dllDirectory = getDllDirectory();
        uiData.modNames = listMods(dllDirectory.c_str());
        uiData.onLoadPressed = &onLoadPressed;
        uiData.onUnloadPressed = &onUnloadPressed;
        StartUI(&uiData);
        printf("Dungeoneer ready.\n");

        bool res = InitConsole(&spyData);
        if (res == false) {
            printf("No console\n");
        }

    }
    else if (dwReason == DLL_PROCESS_DETACH) {

        printf("detach dll\n");

        bool result = DeInitSpy(&spyData);

        printf("detach %s\n", result ? "successful" : "failed");
    }
    return TRUE;
}

// TODO rename to initializeMod?
HMODULE loadMod(LPCSTR filename) {

    HMODULE handle = LoadLibraryA(filename);
    if (handle == NULL) {
        printf("Failed to load dll %s\n", filename);
        return nullptr;
    }
    printf("%s loaded\n", filename);

    typedef ModuleInfo* (__stdcall *FuncModGetInfo)();
    FuncModGetInfo fnModGetInfo  = (FuncModGetInfo)GetProcAddress(handle, "ModGetInfo");
    if (fnModGetInfo == NULL) {
        printf("No ModGetInfo function in %s\n", filename);
        FreeLibrary(handle);
        return nullptr;
    }
    ModuleInfo *modInfo = fnModGetInfo();
    printf("Mod Name %s\n", modInfo->Name);
    printf("ModDungeoneerVersion %s\n", modInfo->DungeoneerVersion);

    FuncModInit fnModInit = (FuncModInit)GetProcAddress(handle, "ModInit");
    if (fnModInit == NULL) {
        printf("No InitMod function in %s\n", filename);
        FreeLibrary(handle);
        return nullptr;
    }

    Module *module = new Module{handle, filename, modInfo};
    loadedModules[filename] = module;

    fnModInit(&dng, module);

    printf("%s initialized\n", filename);

    return handle;
}

bool unloadMod(LPCSTR filename) {

    Module *mod = loadedModules.at(filename);

    ClearFunctionHandlers(mod);

    loadedModules.erase(filename);
    delete mod;

    HMODULE handle = mod->handle;
    if (FreeLibrary(handle) == FALSE) {
        printf("Unable to free library\n");
        return false;
    }

    return true;
}

// TODO Return ModuleInfo?
HMODULE loadModLibrary(LPCSTR filename) {
    
    HMODULE handle = LoadLibraryA(filename);
    if (handle == NULL) {
        printf("Failed to load dll %s\n", filename);
        return nullptr;
    }
    printf("Mod %s\n", filename);

    FuncModGetInfo fnModGetInfo  = (FuncModGetInfo)GetProcAddress(handle, "ModGetInfo");
    if (fnModGetInfo == NULL) {
        printf("No ModGetInfo function in %s\n", filename);
        FreeLibrary(handle);
        return nullptr;
    }
    ModuleInfo *modInfo = fnModGetInfo();
    printf("Mod Name %s\n", modInfo->Name);
    printf("Mod DungeoneerVersion %s\n", modInfo->DungeoneerVersion);

    return handle;
}


bool unloadModLibrary(HMODULE handle) {

    if (FreeLibrary(handle) == FALSE) {
        printf("Unable to free library\n");
        return false;
    }

    return true;
}

// A bit crazy, if we load the wrong dll its DllMain can cause havoc.
// TODO https://docs.microsoft.com/en-gb/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibraryexa?redirectedfrom=MSDN
// with either DONT_RESOLVE_DLL_REFERENCES or one of the recommended options.
std::vector<std::string> listMods(std::string directory) {
    std::vector<std::string> foundMods;

    char search[MAX_PATH];
    sprintf(&search[0], "%s\\*-mod.dll", directory.c_str());
    WIN32_FIND_DATAA ffd;
    HANDLE hFind = INVALID_HANDLE_VALUE;

    hFind = FindFirstFileA(search, &ffd);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("No files found?\n");
        return foundMods;
    }
    do {
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            continue;
        }

        char fullpath[MAX_PATH];
        sprintf(&fullpath[0], "%s\\%s", directory.c_str(), ffd.cFileName);
        HMODULE handle = loadModLibrary(fullpath);
        if (handle == nullptr) {
            continue;
        }
        std::string filename = ffd.cFileName;
        foundMods.push_back(filename);
        unloadModLibrary(handle);

    }
    while (FindNextFileA(hFind, &ffd) != 0);

    return foundMods;
}

std::string getDllDirectory() {
    char path[MAX_PATH];
    HMODULE hm = NULL;
    std::string pathname;

    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | 
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCSTR) &getDllDirectory, &hm) == 0) {
        int ret = GetLastError();
        printf("GetModuleHandle failed, error = %d\n", ret);
        return pathname;
        // Return or however you want to handle an error.
    }
    if (GetModuleFileNameA(hm, path, MAX_PATH) == 0) {
        int ret = GetLastError();
        printf("GetModuleFileName failed, error = %d\n", ret);
        // Return or however you want to handle an error.
        return pathname;
    }
    std::string fullname = path;
    size_t lastindex = fullname.find_last_of("\\"); 
    pathname = fullname.substr(0, lastindex); 
    return pathname;
}

// void AddProcessEventHandler(void *fnHandler) {
//     const std::lock_guard<std::mutex> lock(processEventHandlersMutex);
//     processEventHandlers.push_back(fnHandler);
//     //printf("added %s\n", handler->filterName);
// }

// void AddPostRenderHandler(tPostRender handler) {
//     const std::lock_guard<std::mutex> lock(postRenderHandlersMutex);
//     postRenderHandlers.push_back(handler);
// }

// // TEMP Just for testing loading/unloading dll
// void ClearProcessEventHandlers() {
//     const std::lock_guard<std::mutex> lock(processEventHandlersMutex);
//     processEventHandlers.clear();
// }


// // TEMP Just for testing loading/unloading dll
// void ClearPostRenderHandlers() {
//     const std::lock_guard<std::mutex> lock(postRenderHandlersMutex);
//     postRenderHandlers.clear();
// }

HMODULE temp = nullptr;
void onLoadPressed(const char *modName) {
    printf("loading mod %s\n", modName);

    char fullname[MAX_PATH];
    sprintf(&fullname[0], "%s\\%s", dllDirectory.c_str(), modName);

    HMODULE mod = loadMod(fullname);
    if (mod == nullptr) {
        printf("Unable to load mod %s\n", modName);
        return;
    }

    temp = mod;

}
void onUnloadPressed(const char *modName) {
    printf("unloading %s\n", modName);

    char fullname[MAX_PATH];
    sprintf(&fullname[0], "%s\\%s", dllDirectory.c_str(), modName);

    if (temp != nullptr) {
        unloadMod(fullname);
        temp = nullptr;
    }
}


signed int __stdcall UObject_ProcessEvent(UObject* object, UFunction* func, void* params) {

    int result = spyData.origProcessEvent(object, func, params);

    // Call all handlers
    {
        // const std::lock_guard<std::mutex> lock(processEventHandlersMutex);

        auto it = functionHandlers.find(RefUObject_ProcessEvent);
        if (it == functionHandlers.end()) {
            return result;
        }
        std::list<void *>handlers = it->second;

        for (auto it = handlers.begin(); it != handlers.end(); it++) {
            tProcessEvent fnHandler = (tProcessEvent)*it;
            fnHandler(object, func, params);
        }
    }

	return result;
}


signed int __stdcall AActor_ProcessEvent(AActor* thisActor, UFunction* func, void* params) {
    
    int result = spyData.origAActor_ProcessEvent(thisActor, func, params);
    
    // Call all handlers
    {
        // const std::lock_guard<std::mutex> lock(processEventHandlersMutex);

        auto it = functionHandlers.find(RefAActor_ProcessEvent);
        if (it == functionHandlers.end()) {
            return result;
        }
        std::list<void *>handlers = it->second;

        for (auto it = handlers.begin(); it != handlers.end(); it++) {
            tAActor_ProcessEvent fnHandler = (tAActor_ProcessEvent)*it;
            fnHandler(thisActor, func, params);
        }
    }

	return result;
}

void __stdcall AHUD_PostRender(void* hud) {

    spyData.origPostRender(hud);

    {

        auto it = functionHandlers.find(RefAHUD_PostRender);
        if (it == functionHandlers.end()) {
            return;
        }
        std::list<void *>handlers = it->second;

        for (auto it = handlers.begin(); it != handlers.end(); it++) {
            tPostRender fnHandler = (tPostRender)*it;
            fnHandler(hud);
        }
    }
}

