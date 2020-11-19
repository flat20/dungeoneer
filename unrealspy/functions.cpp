#include "functions.h"

namespace spy {
    namespace functions {
        FunctionAddr<tUObject_ProcessEvent> UObject_ProcessEvent("40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC F0 00 00 00 48 8D 6C 24 30 48 89 9D 18 01 00 00");
        // Needs work for 4.24

        FunctionAddr<tAActor_ProcessEvent> AActor_ProcessEvent("48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B 01 49 8B F0 ?? ?? ?? ?? ?? ?? ?? 48 8B EA 48 8B D9");
        FunctionAddr<tAHUD_PostRender> AHUD_PostRender("40 55 56 48 8D 6C 24 B1 48 81 EC C8 00 00 00 48 8B 01 48 8B F1");
    }
}
