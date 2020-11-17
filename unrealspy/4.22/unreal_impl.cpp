// GEngine, GUObjectArray, etc
#include "unreal_impl.h"
#include <unrealspy.h>
#include "helpers.h"

namespace spy {
    FUObjectArray *GUObjectArray = nullptr;
    TNameEntryArray *GNames = nullptr;
    UEngine* GEngine = nullptr;
}

// TODO Rename
bool spy::initVars() {

    printf("initing vars\n");
//     // We can get GNames by calling FName::GetNames()
//     //FName_GetNames GetNames = (FName_GetNames)data.functionPtrs[RefFName_GetNames];

    if (GNames == nullptr) {
        TNameEntryArray& names = GetFunction<tFName_GetNames>(RefFName_GetNames)();
        spy::GNames = &names;
    }

//     // We can get GUObjectArray by instantiating FRawObjectIterator. It just so happens that it
//     // holds a reference to GUObjectArray as its first member
    if (GUObjectArray == nullptr) {
        char bla[256];
        auto objectIteratorCtor = (tFRawObjectIterator_Ctor)data.functionPtrs[RefFRawObjectIterator_Ctor];
        void **ref = (void**)objectIteratorCtor(&bla[0], false);
        GUObjectArray = (FUObjectArray*)*ref;
        printf("GUObjectArray? %llx\n", (uintptr_t)GUObjectArray);
    }

    // When we have names and objects, get uengine
    if (spy::GEngine == nullptr && spy::GUObjectArray != nullptr && spy::GNames != nullptr) {
        UObject *engine = FindObjectByName("GameEngine", "GameEngine", nullptr);
        printf("gengine? %llx\n", (uintptr_t)engine);
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


UClass* UClass::GetPrivateStaticClass() {
    static UClass* cls = (UClass*)spy::FindObjectByName("Class", "Class", nullptr);
    printf("UClass:: %llx\n", (uintptr_t)cls);
    return cls;
}

//#pragma comment(linker, "/export:?ZeroVector@FVector@@2U1@B")
CORE_API const FVector FVector::ZeroVector(0.0f, 0.0f, 0.0f);