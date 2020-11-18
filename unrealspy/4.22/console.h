#pragma once
#include "unrealspy.h"

typedef void (__thiscall *tUConsole_ConsoleCommand)(UConsole *thisUConsole, const FString *Command);
typedef void (__thiscall *tFConsoleManager_ProcessUserConsoleInput) (FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);

namespace spy {
    namespace functions {
        static FunctionAddr<tFConsoleManager_ProcessUserConsoleInput> FConsoleManager_ProcessUserConsoleInput("48 8B C4 4C 89 48 20 4C 89 40 18 48 89 48 08 55 56 48 8D 68 A1 48 81 EC B8 00 00 00 33 F6");
    }
}

namespace spy {
    bool InitConsole();
    bool InitCheatCommands(std::function<void (bool result)> fnResult);
}
void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);
//bool InitConsole(SpyData *data);

