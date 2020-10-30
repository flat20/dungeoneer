#pragma once

#include <cstdint>

namespace spy {

    struct Hook {
        uintptr_t address;
        const void *detour;       // Function to call
        void *original;    // original implementation
    };
}

bool InitHook();
bool SetHook(void *target, const void *detour, void* *original);
// Address to target and address to our hook
bool SetHook(spy::Hook *hook);
bool EnableHook(uintptr_t address);
bool RemoveHook(spy::Hook *hook);

