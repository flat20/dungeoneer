// GEngine, GUObjectArray, etc
#include "unreal_impl.h"
#include <diet-ue.h>

namespace spy {
    FUObjectArray *GUObjectArray = nullptr;
    //TNameEntryArray *GNames = nullptr;
    UEngine* GEngine = nullptr;
}

UClass* UClass::GetPrivateStaticClass() {
    static UClass* cls = (UClass*)spy::FindObjectByName(TEXT("Class"), TEXT("Class"), nullptr);
    printf("UClass:: %llx\n", (uintptr_t)cls);
    return cls;
}

CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);