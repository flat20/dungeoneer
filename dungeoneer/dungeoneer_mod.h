#pragma once
#include <windows.h>
#include <dungeoneer.h>
#include <util.h>

#define DLL_EXPORT extern "C" __declspec(dllexport)

// entry function for a mod.
void ModMain(Dungeoneer *dng, Module *mod);


extern ModuleInfo modInfo; // extern because the mod .cpp file will declare it.
DLL_EXPORT ModuleInfo* ModGetInfo() {
    return &modInfo;
}

// Need to setup util:: with the global GNames.
DLL_EXPORT void ModInit(Dungeoneer *dng, Module *mod) {
    util::GNames = dng->spyData->GNames;
    util::GUObjectArray = dng->spyData->GUObjectArray;
    ModMain(dng, mod);
}

BOOL WINAPI DllMain(HINSTANCE hinst, DWORD dwReason, LPVOID reserved) {
    if (dwReason == DLL_PROCESS_ATTACH) {
    }
    else if (dwReason == DLL_PROCESS_DETACH) {
    }
    return TRUE;
}