// GEngine, GUObjectArray, etc
#include "unreal_impl.h"
#include <unrealspy.h>
#include "helpers.h"

namespace spy {
    SPYAPI FUObjectArray *GUObjectArray = nullptr;
    SPYAPI TNameEntryArray *GNames = nullptr;
    SPYAPI UEngine* GEngine = nullptr;
}

namespace spy {

    namespace functions {
        FunctionAddr<tFName_GetNames> FName_GetNames("48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20");
        FunctionAddr<tFRawObjectIterator> FRawObjectIterator("84 D2 48 C7 41 10 00 00 00 00 B8 FF FF FF FF ?? ?? ?? ?? ?? ?? ?? 89 41 08 4C 8B D1 4C 89 01");
        FunctionAddr<tStaticConstructObject_Internal> StaticConstructObject_Internal("40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 50 FF FF FF 48 81 EC B0 01 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 A8 00 00 00");
        FunctionAddr<tUConsole_ConsoleCommand> UConsole_ConsoleCommand("48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 30 48 8B F2 48 89 54 24 40 48 8B D9 48 8D 54 24 40 48 83 C1 68");
    }

}


// TODO Rename
bool spy::initVars() {

    if (GNames == nullptr) {
        TNameEntryArray& names = functions::FName_GetNames.Call();
        spy::GNames = &names;
    }

    // We can get GUObjectArray by instantiating FRawObjectIterator. It just so happens that it
    // holds a reference to GUObjectArray as its first member
    if (GUObjectArray == nullptr) {
        char bla[256];
        auto objectIteratorCtor = functions::FRawObjectIterator.Call;
        void **ref = (void**)objectIteratorCtor(&bla[0], false);
        GUObjectArray = (FUObjectArray*)*ref;
    }

    // When we have names and objects, get uengine
    if (spy::GEngine == nullptr && spy::GUObjectArray != nullptr && spy::GNames != nullptr) {
        UObject *engine = FindObjectByName("GameEngine", "GameEngine", nullptr);
        if (engine != nullptr) {
            GEngine = (UEngine*)engine;
        }

    }

    // Still haven't got all variables
    if (spy::GNames == nullptr || spy::GUObjectArray == nullptr || spy::GEngine == nullptr) {
        return false;
    }

    return true;
}

#pragma comment(linker, "/export:?GetPrivateStaticClass@UClass@@CAPEAV1@XZ")
UClass* UClass::GetPrivateStaticClass() {
    static UClass* cls = (UClass*)spy::FindObjectByName("Class", "Class", nullptr);
    return cls;
}

#pragma comment(linker, "/export:?ZeroVector@FVector@@2U1@B")
CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);