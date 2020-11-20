#pragma once

// Done in make.bat now.
//#pragma comment(lib, "dungeoneer.lib")
//#define SPYAPI __declspec(dllimport)

#include <dungeoneer.h>

// All this just for HMODULE
#include <Windows/AllowWindowsPlatformTypes.h>
	#include <windows.h>
#include <Windows/HideWindowsPlatformTypes.h>

#define DLL_EXPORT extern "C" __declspec(dllexport)

// entry function for a mod.
void ModMain(Dungeoneer *dng, Module *mod);


extern ModuleInfo modInfo; // extern because the mod .cpp file will declare it.
DLL_EXPORT ModuleInfo* ModGetInfo() {
    return &modInfo;
}

// Need to setup util:: with the global GNames.
DLL_EXPORT void ModInit(Dungeoneer *dng, Module *mod) {
    spy::GUObjectArray = dng->GUObjectArray;
    spy::GNames = dng->GNames;
    spy::GEngine = dng->GEngine;
    ModMain(dng, mod);
}

// Add a ConfigDraw()

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
    }
    return 1;
}