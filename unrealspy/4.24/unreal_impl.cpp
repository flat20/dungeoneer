// GEngine, GUObjectArray, etc
#include "unreal_impl.h"
#include <diet-ue.h>
#include "helpers.h"

namespace spy {
    FUObjectArray *GUObjectArray = nullptr;
    //TNameEntryArray *GNames = nullptr;
    UEngine* GEngine = nullptr;
}


// TODO rename
bool spy::initVars() {

    if (spy::GUObjectArray == nullptr) {
        // Passing in a fake UClass to satisfy the code and make it not crash.
        char bla[256];
        auto objectIteratorCtor = (tFObjectIterator_Ctor)data.functionPtrs[RefFObjectIterator_Ctor];
        void **ref = (void**)objectIteratorCtor(&bla[0], (UClass*)&bla[0], false, EObjectFlags::RF_NoFlags, EInternalObjectFlags::None);
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
    printf("UClass:: %llx\n", (uintptr_t)cls);
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