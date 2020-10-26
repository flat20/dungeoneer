#include <Windows.h>
#include <stdio.h>
#include <thread>

#include <unrealspy.h>
#include <offsets.h>
#include <util.h>
#include <console.h>
#include <fstream>
#include <utility>
#include "json.hpp"

#include "ui.h"

//void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);

spy::Data *spyData;
UIData uiData;
std::string dllPath;

void Init();

// Testing: Params passed to LoadLevel. Not completed, but has what we need for now.
struct LoadLevelParams {
    byte difficulty;        //0 +8
    byte threatLevel;
    TArray<TCHAR> loadType; //8 +16 "lobby", "ingame"
    uint64 something;       //20 +8 0x17, 
    TArray<TCHAR> levelName; //28 +16 "Lobby", "soggyswamp"
    int32 seed;            //44 Could be uint32 as well.
    TArray<TArray<TCHAR>> characterUnlockKeys;
    // Probably more stuff, but stopped looking for now.
};

// __int64 __fastcall subLevelLoad(__int64 a1, __int64 a2, char a3)
typedef void (__fastcall *tLoadLevel)(UObject* thisBpGameInstance, LoadLevelParams *params, byte r8b, double xmm3, DWORD64 stackFloat);
void LoadLevel(UObject* thisBpGameInstance, LoadLevelParams *params, byte r8b, double xmm3, DWORD64 stackFloat);


using namespace util;


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {

    if (dwReason == DLL_PROCESS_ATTACH) {


        char dllFilename[MAX_PATH];
        DWORD len = GetModuleFileNameA(hinst, (LPSTR)&dllFilename, sizeof(dllFilename));
        if (len == 0) {
            printf("No dll filename?\n");
            return FALSE;
        }
        std::string filename = dllFilename;
        size_t pos = filename.find_last_of("/\\");
        dllPath = filename.substr(0,pos);

        AllocConsole();
        freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    
        // Init in separate thread.
        // Works in a dll as long as we don't wait for thread to join
        std::thread t(Init);
        t.detach();

    }
    else if (dwReason == DLL_PROCESS_DETACH) {

        // bool result = true;//DeInitSpy(&spyData);

        // printf("detach %s\n", result ? "successful" : "failed");
    }
    return TRUE;
}

// Initializing in a separate thread
void Init() {
    
    uiData.levels = {
        {"creeperwoods",        0},
        {"pumpkinpastures",     0},
        {"soggyswamp",          0},
        {"fieryforge",          0},
        {"deserttemple",        0},
        {"highblockhalls",      0},
        {"obsidianpinnacle",    0},
        {"cacticanyon",         0},
    };


    // Read launcher_settings.json for Minecraft Dungeons path
    using json = nlohmann::json;
    std::string filename = "speedrun_defaults.json";

    printf("Reading %s\\%s\n", dllPath.c_str(), filename.c_str());
    std::ifstream in(dllPath + "\\" + filename);
    if (in.is_open() == true) {
        json j;
        in >> j;
        
        // It's ordered by key.. Unfortunately
        uiData.levels = j.get<std::map<std::string,int32_t>>();

        // uiData.levels.clear();
        // for(auto &entry: levels) {
        //     printf("%s\n", entry.first.c_str());
        //     uiData.levels[entry.first] = entry.second;
        // }

        in.close();
    } else {
        printf("File not found\n");
    }


    StartUI(&uiData);

    spyData = spy::Init(offsets::defaultAddressLookups);
    if (spyData == nullptr) {
        printf("Unable to init Unreal Spy\n");
        return;
    }

    spy::HookFunctionRef(RefLoadLevel, &LoadLevel, nullptr);


    bool result = spy::EnableConsole([](bool result) {
        printf("Console enabled with all commands\n");
    });
    if (result == false) {
        printf("No console\n");
    }

}

void LoadLevel(UObject* thisBpGameInstance, LoadLevelParams *params, byte r8b, double xmm3, DWORD64 stackFloat) {
    printf("LevelLoad\n");
    printf("  Name: %ws\n", (wchar_t*)params->levelName.Data);
    printf("  Seed: %I32d\n", params->seed);

    // Lazy convert from wchar to char
    wchar_t* ln = (wchar_t*) params->levelName.Data;
    std::wstring ws( ln );

    // Not sure how to cast the iterators so just disabled the warnings..
    #pragma warning(disable : 4244)
    std::string levelName( ws.begin(), ws.end() );

    auto element = uiData.levels.find(levelName);
    if (element != uiData.levels.end()) {
        params->seed = element->second;
        printf("  New Seed: %I32d\n", params->seed);
    }


    ((tLoadLevel)spy::data.hooks[RefLoadLevel]->original)(thisBpGameInstance, params, r8b, xmm3, stackFloat);
    return;
}