#include "hook.h"

#include <windows.h>

#include <MinHook.h>
#include <stdio.h>

bool InitHook() {
    // Hook functions
    if (MH_Initialize() != MH_OK) {
        printf("MH_Initialize failed. No hooking will work\n");
        return false;
    }
    return true;
}


// Address to target and address to our hook
bool SetHook(void *target, const void* detour, void* *original) {

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