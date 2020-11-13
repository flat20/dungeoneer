//#include <Windows.h>
#include <stdio.h>
#include <thread>

#include <unrealspy.h>
#include <uhook.h>
#include <offsets.h>
#include <console.h>
#include <fstream>
#include <utility>

//void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);

spy::Data *spyData;
std::string dllPath;

void Init();

// Testing: Params passed to LoadLevel. Not completed, but has what we need for now.
struct LoadLevelParams {
    uint8 difficulty;        //0 +8
    uint8 threatLevel;
    TArray<TCHAR> loadType; //8 +16 "lobby", "ingame"
    uint64 something;       //20 +8 0x17, 
    TArray<TCHAR> levelName; //28 +16 "Lobby", "soggyswamp"
    int32 seed;            //44 Could be uint32 as well.
    TArray<TArray<TCHAR>> characterUnlockKeys;
    // Probably more stuff, but stopped looking for now.
};

// __int64 __fastcall subLevelLoad(__int64 a1, __int64 a2, char a3)
typedef void (__fastcall *tLoadLevel)(UObject* thisBpGameInstance, LoadLevelParams *params, uint8 r8b, double xmm3, DWORD64 stackFloat);
void LoadLevel(UObject* thisBpGameInstance, LoadLevelParams *params, uint8 r8b, double xmm3, DWORD64 stackFloat);


BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {

    if (dwReason == DLL_PROCESS_ATTACH) {


        char dllFilename[MAX_PATH];
        DWORD len = GetModuleFileNameA(hinst, (LPSTR)&dllFilename, sizeof(dllFilename));
        if (len == 0) {
            printf("No dll filename?\n");
            return 0;
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
    return 1;
}

// Initializing in a separate thread
void Init() {

    spyData = spy::Init(offsets::defaultAddressLookups);
    if (spyData == nullptr) {
        printf("Unable to init Unreal Spy\n");
        return;
    }

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

}
