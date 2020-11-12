//#include <Windows.h>
//#include <stdio.h>
#include <list>
#include <map>
#include <thread>
#include <mutex>

//#include <util.h>
#include <console.h>

#include "dungeoneer.h"
#include "ui.h"

#include <offsets.h>


signed int __stdcall UObject_ProcessEvent(UObject* object, UFunction* func, void* params);
signed int __stdcall AActor_ProcessEvent(AActor* thisActor, UFunction* func, void* params);
void __stdcall AHUD_PostRender(void* hud);
void* __stdcall GetNames();

HMODULE loadMod(LPCSTR filename);
std::string getDllDirectory();

// TODO Maybe in Dungeoneer data
std::string dllDirectory;

// Global function handlers for all mods.
std::map<UE4Reference,std::list<void *>> functionHandlers;
std::mutex functionHandlersMutex;

// Lookup for loaded modules.
std::map<std::string,Module*> loadedModules;

void Init();
void __stdcall AddFunctionHandler(Module *mod, UE4Reference funcName, void *fnHandler);
void RemoveFunctionHandler(Module *mod, UE4Reference funcName, void *fnHandler);
void ClearFunctionHandlers(Module *mod);

void onLoadPressed(const char *);
void onUnloadPressed(const char *);
void ClearPostRenderHandlers();
void ClearProcessEventHandlers();
std::vector<std::string> listMods(std::string directory);



Dungeoneer dng;
spy::Data *spyData;
UIData uiData;

// TODO just make a std::map or similar
tUObject_ProcessEvent origUObject_ProcessEvent = NULL;
tAActor_ProcessEvent origAActor_ProcessEvent = NULL;
tAHUD_PostRender origAHUD_PostRender = NULL;


// Testing: Params passed to LoadLevel. Not completed, but has what we need for now.
struct LoadLevelParams {
    uint8 difficulty;
    uint8 threatLevel;
    TArray<TCHAR> loadType; // "lobby", "ingame"
    uint64 something;   // 0x17, 
    TArray<TCHAR> levelName; // "Lobby", "soggyswamp"
    uint64 seed;    // Could be uint32 as well.
    TArray<TArray<TCHAR>> characterUnlockKeys;
    // Probably more stuff, but stopped looking for now.
};

// __int64 __fastcall subLevelLoad(__int64 a1, __int64 a2, char a3)
typedef void (__fastcall *tLoadLevel)(UObject* thisBpGameInstance, LoadLevelParams *params, uint8 r8b, double xmm3, DWORD64 stackFloat);
void LoadLevel(UObject* thisBpGameInstance, LoadLevelParams *params, uint8 r8b, double xmm3, DWORD64 stackFloat);


//using namespace util;


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {

    if (dwReason == DLL_PROCESS_ATTACH) {

        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

        // Init in separate thread.
        // Works in a dll as long as we don't wait for thread to join
        std::thread t(Init);
        t.detach();

    }
    else if (dwReason == DLL_PROCESS_DETACH) {

    }
    return 1;
}

void Init() {

    // // Some ui vars
    dllDirectory = getDllDirectory();
    uiData.modNames = listMods(dllDirectory.c_str());
    uiData.onLoadPressed = &onLoadPressed;
    uiData.onUnloadPressed = &onUnloadPressed;
    uiData.modsDisabled = true; // Until Init is done.
    StartUI(&uiData);

    // Can block for up to 60s until it finds all vars.
    // We run in a thread for that reason
    spyData = spy::Init(offsets::defaultAddressLookups);
    if (spyData == nullptr) {
        printf("Failed to initialize unrealspy\n");
        return;
    }

    // https://docs.unrealengine.com/en-US/Programming/BuildTools/UnrealBuildTool/ThirdPartyLibraries/index.html

    spy::HookFunctionRef(RefUObject_ProcessEvent, &UObject_ProcessEvent, (void**)&origUObject_ProcessEvent);
    spy::HookFunctionRef(RefAActor_ProcessEvent, &AActor_ProcessEvent, (void**)&origAActor_ProcessEvent);
    spy::HookFunctionRef(RefAHUD_PostRender, &AHUD_PostRender, (void**)&origAHUD_PostRender);
    // Testing
    spy::HookFunctionRef(RefLoadLevel, &LoadLevel, nullptr);

    dng.GUObjectArray = spy::GUObjectArray;
    dng.GNames = spy::GNames;
    dng.GEngine = spy::GEngine;

    dng.spyData = spyData;
    dng.AddFunctionHandler = &AddFunctionHandler;

    uiData.modsDisabled = false;

    if (spy::InitConsole() == false) {
        printf("Unable to init console");
        return;
    }

    printf("Console enabled\n");
    bool result = spy::InitCheatCommands([](bool result) {
        printf("Cheat commands enabled\n");
    });
    if (result == false) {
        printf("No cheat commands\n");
    }

    printf("Dungeoneer ready\n");
}

void __stdcall AddFunctionHandler(Module *mod, UE4Reference funcName, void *fnHandler) {
    std::lock_guard<std::mutex> guard(functionHandlersMutex);

    mod->functionHandlers[funcName] = fnHandler;

    functionHandlers[funcName].push_back(fnHandler);

}

void RemoveFunctionHandler(Module *mod, UE4Reference funcName, void *fnHandler) {
    std::lock_guard<std::mutex> guard(functionHandlersMutex);

    mod->functionHandlers.erase(funcName);
    
    functionHandlers[funcName].remove(fnHandler);
}

void ClearFunctionHandlers(Module *mod) {
    std::lock_guard<std::mutex> guard(functionHandlersMutex);

    for (auto it = mod->functionHandlers.begin(); it !=  mod->functionHandlers.end(); it++) {
        UE4Reference funcName = it->first;
        void *fnHandler = it->second;
        functionHandlers[funcName].remove(fnHandler);
        if (functionHandlers[funcName].size() == 0) {
            functionHandlers.erase(funcName);
        }
    }

    mod->functionHandlers.clear();
}



// TODO rename to initializeMod?
HMODULE loadMod(LPCSTR filename) {

    HMODULE handle = LoadLibraryA(filename);
    if (handle == NULL) {
        printf("Failed to load dll %s (%ld)\n", filename, GetLastError());
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
    printf("ConfigDraw: %llx\n", (uintptr_t)modInfo->ConfigDraw);

    FuncModInit fnModInit = (FuncModInit)GetProcAddress(handle, "ModInit");
    if (fnModInit == NULL) {
        printf("No InitMod function in %s\n", filename);
        FreeLibrary(handle);
        return nullptr;
    }

    Module *module = new Module{handle, filename, modInfo};
    loadedModules[filename] = module;

    fnModInit(&dng, module);

    uiData.modConfigDraws.push_back(modInfo->ConfigDraw);

    printf("%s initialized\n", filename);

    return handle;
}

bool unloadMod(LPCSTR filename) {

    Module *mod = loadedModules.at(filename);

    // TODO Make map, and remove it
    if (mod->info->ConfigDraw != nullptr) {
        uiData.modConfigDraws.remove(mod->info->ConfigDraw);
    }

    ClearFunctionHandlers(mod);

    loadedModules.erase(filename);
    delete mod;

    HMODULE handle = (HMODULE)mod->handle;
    if (FreeLibrary(handle) == 0) {
        printf("Unable to free library\n");
        return false;
    }

    return true;
}


// TODO Return ModuleInfo?
HMODULE loadModLibrary(LPCSTR filename) {
    HMODULE handle = LoadLibraryA(filename);
    if (handle == NULL) {
        printf("Failed to load dll %s %ld\n", filename, GetLastError());
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

    if (FreeLibrary(handle) == 0) {
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

bool firstTime = true;
signed int __stdcall UObject_ProcessEvent(UObject* object, UFunction* func, void* params) {

    int result = origUObject_ProcessEvent(object, func, params);

    // Call all handlers
    {
        std::unique_lock<std::mutex> guard(functionHandlersMutex);

        auto it = functionHandlers.find(RefUObject_ProcessEvent);
        if (it == functionHandlers.end()) {
            return result;
        }
        std::list<void *>handlers = it->second;

        // Unlock?
        guard.unlock();

        for (auto it = handlers.begin(); it != handlers.end(); it++) {
            tUObject_ProcessEvent fnHandler = (tUObject_ProcessEvent)*it;
            fnHandler(object, func, params);
        }
    }

	return result;
}


signed int __stdcall AActor_ProcessEvent(AActor* thisActor, UFunction* func, void* params) {
    
    int result = origAActor_ProcessEvent(thisActor, func, params);
    
    // Call all handlers
    {
        std::unique_lock<std::mutex> guard(functionHandlersMutex);

        auto it = functionHandlers.find(RefAActor_ProcessEvent);
        if (it == functionHandlers.end()) {
            return result;
        }
        std::list<void *>handlers = it->second;

        guard.unlock();

        for (auto it = handlers.begin(); it != handlers.end(); it++) {
            auto fnHandler = (tAActor_ProcessEvent)*it;
            fnHandler(thisActor, func, params);
        }
    }

	return result;
}

void __stdcall AHUD_PostRender(void* hud) {

    origAHUD_PostRender(hud);

    {

        std::unique_lock<std::mutex> guard(functionHandlersMutex);
        auto it = functionHandlers.find(RefAHUD_PostRender);
        if (it == functionHandlers.end()) {
            return;
        }
        std::list<void *>handlers = it->second;

        guard.unlock();
    
        for (auto it = handlers.begin(); it != handlers.end(); it++) {
            auto fnHandler = (tAHUD_PostRender)*it;
            fnHandler(hud);
        }
    }
}

// Just for testing LoadLevel

void LoadLevel(UObject* thisBpGameInstance, LoadLevelParams *params, uint8 r8b, double xmm3, DWORD64 stackFloat) {
    // printf("level loaded? %s\n", util::getName(thisBpGameInstance));
    printf("I have no idea if this code will work!?!? GetData() is inline so can we use it?\n");
    printf("levelName: %ws\n", (wchar_t*)params->levelName.GetData());
    printf("loadType: %ws\n", (wchar_t*)params->loadType.GetData());
    printf("seed: %I64d\n", params->seed);
//    params->seed = 91081;

    ((tLoadLevel)spy::GetHook(RefLoadLevel)->original)(thisBpGameInstance, params, r8b, xmm3, stackFloat);
    return;
}