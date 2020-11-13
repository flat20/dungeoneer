#pragma once
#include "unrealspy.h"

typedef void (__thiscall *tUConsole_ConsoleCommand)(UConsole *thisUConsole, const FString *Command);
typedef void (__thiscall *tFConsoleManager_ProcessUserConsoleInput) (FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);

namespace spy {
    bool InitConsole();
    bool InitCheatCommands(std::function<void (bool result)> fnResult);
}

void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);

