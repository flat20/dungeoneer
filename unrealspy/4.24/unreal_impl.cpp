// GEngine, GUObjectArray, etc
#include "unreal_impl.h"
#include <diet-ue.h>

namespace spy {
    FUObjectArray *GUObjectArray = nullptr;
    //TNameEntryArray *GNames = nullptr;
    UEngine* GEngine = nullptr;
}

CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);