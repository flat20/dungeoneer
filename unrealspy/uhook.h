#pragma once

#include <cstdint>
#include "unrealspy.h"

namespace spy {

    struct Hook {
        uintptr_t address;
        const void *detour;       // Function to call
        void *original;    // original implementation
    };

    bool HookFunctionRef(::offsets::OpcodeAddress& func, const void *detour, void **original);
    bool UnhookFunctionRef(::offsets::OpcodeAddress& func);

    bool InitHook();
    bool SetHook(void *target, const void *detour, void* *original);
    // Address to target and address to our hook
    bool SetHook(Hook *hook);
    // Get rid if we're not using it.
    Hook *GetHook(::offsets::OpcodeAddress& func);
    bool EnableHook(uintptr_t address);
    bool RemoveHook(Hook *hook);


}
