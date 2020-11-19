// GEngine, GUObjectArray, etc
#include "unreal_impl.h"
#include <diet-ue.h>
#include "helpers.h"

namespace spy {
    FUObjectArray *GUObjectArray = nullptr;
    UEngine* GEngine = nullptr;
}

namespace spy {

    namespace functions {
        FunctionAddr<tFObjectIterator> FObjectIterator("48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 44 8B 54 24 50");
        FunctionAddr<tStaticConstructObject_Internal> StaticConstructObject_Internal("4C 89 44 24 18 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 48 FF FF FF 48 81 EC B8 01 00 00");
        FunctionAddr<tUConsole_ConsoleCommand> UConsole_ConsoleCommand("48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 30 83 7A 08 00 48 8D");

        FunctionAddr<tFName_GetEntry> FName_GetEntry("40 53 48 83 EC 20 8B D9 0F B7 C1 C1 EB 10 ?? ?? ?? ?? ?? ?? ?? 89 5C 24 38 89 44 24 3C");
    }

    std::vector<offsets::OpcodeAddress*> defaultFunctionLookups = {
        &functions::FObjectIterator,
        &functions::StaticConstructObject_Internal,
        &functions::UConsole_ConsoleCommand,
        &functions::FName_GetEntry,
    };

}

// TODO rename
bool spy::initVars() {

    if (spy::GUObjectArray == nullptr) {
        // Passing in a fake UClass to satisfy the code and make it not crash.
        char bla[256];
        auto objectIteratorCtor = functions::FObjectIterator.Call;
        void **ref = (void**)objectIteratorCtor((FObjectIterator*)&bla[0], (UClass*)&bla[0], false, EObjectFlags::RF_NoFlags, EInternalObjectFlags::None);
        spy::GUObjectArray = (FUObjectArray*)*ref;
    }

    // When we have objects, get uengine
    if (spy::GEngine == nullptr && spy::GUObjectArray != nullptr) {

        //00007FF7BE524F90 - 00007FF7BA8E0000 = 3C44F90
        // MATCH! GameEngine_2147482615
        //        GameEngine_2147482615
        // StaticConstructObject_Internal = 0

        UEngine *actual = *(UEngine**)(data.baseAddress + (uintptr_t)0x3C44F90);
        printf("actual? %llx\n", (uintptr_t)actual);

        UObject *engine = FindObjectByName("GameEngine", "GameEngine", nullptr); // "/Engine/Transient"
        printf("%s\n", GetName(engine));
        printf("%s\n", GetName(engine->GetClass()));
        printf("%s\n", GetName(engine->GetOuter()));
        printf("engine? %llx\n", (uintptr_t)engine);
        if (engine != nullptr) {
            spy::GEngine = (UEngine*)engine;
        }

    }

    // Still haven't got all variables
    if (spy::GUObjectArray == nullptr || spy::GEngine == nullptr) {
        return false;
    }

    return true;
}

UClass* UClass::GetPrivateStaticClass() {
    static UClass* cls = (UClass*)spy::FindObjectByName("Class", "Class", nullptr);
    return cls;
}

// For FName matching
void FNameEntry::GetAnsiName(ANSICHAR(&Out)[NAME_SIZE]) const
{
	//check(!IsWide());
	CopyUnterminatedName(Out);
	Out[Header.Len] = '\0';
}

void FNameEntry::CopyUnterminatedName(ANSICHAR* Out) const
{
	FPlatformMemory::Memcpy(Out, AnsiName, sizeof(ANSICHAR) * Header.Len);
    // Does nothing normally.
//	Decode(Out, Header.Len);
}

CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);