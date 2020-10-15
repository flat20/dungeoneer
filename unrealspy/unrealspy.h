#pragma once
#include <map>
#include <functional>
#include "unreal.h"


typedef signed int (__thiscall *tUObject_ProcessEvent) (UObject* thisObject, UFunction* func, void *params);
typedef signed int (__thiscall *tAActor_ProcessEvent) (AActor* thisActor, UFunction* func, void *params);
typedef void (__thiscall *tAHUD_PostRender) (void *hud);
typedef TNameEntryArray* (__stdcall *tFName_GetNames) ();
//typedef FRawObjectIterator *__fastcall FRawObjectIteratorCtor(FRawObjectIterator *this, bool bOnlyGCedObjects);
typedef void* (__thiscall *tFRawObjectIterator_Ctor)(void *_this, bool bOnlyGCedObjects);

// void __stdcall __high AHUD::DrawRect(struct FLinearColor, float, float, float, float)
typedef void (__thiscall *tAHUD_DrawRect)(void *hud, FLinearColor RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);

// void __stdcall __high AHUD::DrawText(const struct FString *, struct FLinearColor, float, float, struct UFont *, float, bool)
// 	void DrawText(const FString& Text, FLinearColor TextColor, float ScreenX, float ScreenY, UFont* Font=NULL, float Scale=1.f, bool bScalePosition=false);
typedef void (__thiscall *tAHUD_DrawText)(void *hud, const FString* Text, FLinearColor TextColor, float ScreenX, float ScreenY, UFont* Font, float Scale, bool bScalePosition);

// Sadly does not take linebreaks in to account so no good for multiline, if we care about that.
//void __fastcall AHUD::GetTextSize(AHUD *__hidden this, const struct FString *, float *, float *, struct UFont *, float)
typedef void (__thiscall *tAHUD_GetTextSize)(void *hud, const FString* Text, float* OutWidth, float* OutHeight, UFont* Font, float Scale);

//  UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr, bool bAllowObjectReconciliation = true, FUObjectSerializeContext* InSerializeContext = nullptr );
// _int64 __fastcall StaticLoadObject(struct UClass *a1, struct UObject *a2, const wchar_t *a3, const wchar_t *a4, unsigned int a5, struct UPackageMap *a6, bool a7, struct FUObjectSerializeContext *a8)
typedef UObject* (__fastcall *tStaticLoadObject)(UClass* Class, UObject* Inouter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, void* Sandbox, bool bAllowObjectReconciliation, void *InSerializeContext);

// COREUOBJECT_API UClass* StaticLoadClass(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr);
typedef UClass* (__fastcall *tStaticLoadClass)(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, void* Sandbox);

// COREUOBJECT_API UPackage* LoadPackage( UPackage* InOuter, const TCHAR* InLongPackageName, uint32 LoadFlags, FArchive* InReaderOverride = nullptr, FUObjectSerializeContext* InLoadContext = nullptr );
typedef UPackage* (__fastcall *tLoadPackage)( UPackage* InOuter, const TCHAR* InLongPackageName, uint32 LoadFlags, void* InReaderOverride, void* InLoadContext );

// COREUOBJECT_API UObject* StaticConstructObject_Internal(UClass* Class, UObject* InOuter = (UObject*)GetTransientPackage(), FName Name = NAME_None, EObjectFlags SetFlags = RF_NoFlags, EInternalObjectFlags InternalSetFlags = EInternalObjectFlags::None, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, struct FObjectInstancingGraph* InstanceGraph = nullptr, bool bAssumeTemplateIsArchetype = false);
typedef UObject* (__fastcall *tStaticConstructObject_Internal)(UClass* Class, UObject* InOuter, FName Name, EObjectFlags SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype);
//typedef UObject* (__fastcall *StaticConstructObject_Internal)(__int64 a1,    int a2,           __int64 a3, int a4,                int a5,                                __int64 a6,        char a7,                               __int64 a8,          char a9);

typedef void (__thiscall *tUConsole_ConsoleCommand)(UConsole *thisUConsole, const struct FString *);

// bool FConsoleManager::ProcessUserConsoleInput(const TCHAR* InInput, FOutputDevice& Ar, UWorld* InWorld)
// __int64 __fastcall FConsoleManager::ProcessUserConsoleInput(FConsoleManager *this, const wchar_t *a2, struct FOutputDevice *a3, struct UWorld *a4)
typedef void (__thiscall *tFConsoleManager_ProcessUserConsoleInput) (FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld);


// We need global access to some predefined functions and names.
// Can't use string enums so maybe this?
typedef std::string UE4Reference;
const UE4Reference RefFName_GetNames                = "FName_GetNames";
const UE4Reference RefFRawObjectIterator_Ctor       = "FRawObjectIterator_Ctor";
const UE4Reference RefUObject_ProcessEvent          = "UObject_ProcessEvent";
const UE4Reference RefAActor_ProcessEvent           = "AActor_ProcessEvent";
const UE4Reference RefAHUD_PostRender               = "AHUD_PostRender";
const UE4Reference RefStaticLoadObject              = "StaticLoadObject";
const UE4Reference RefStaticLoadClass               = "StaticLoadClass";
const UE4Reference RefLoadPackage                   = "LoadPackage";
const UE4Reference RefStaticConstructObject_Internal= "StaticConstructObject_Internal";
const UE4Reference RefUConsole_ConsoleCommand       = "UConsole_ConsoleCommand";    // Run console command
const UE4Reference RefFConsoleManager_ProcessUserConsoleInput = "FConsoleManager::ProcessUserConsoleInput";
const UE4Reference RefAddEmeralds                   = "AddEmeralds";
const UE4Reference RefLoadLevel                     = "LoadLevel";

namespace spy {

    struct Hook {
        uintptr_t address;
        const void *detour;       // Function to call
        LPVOID original;    // original implementation
    };

    struct Data {
        uintptr_t baseAddress;                          // Base address of process, never used but let's leave for now.
        std::map<UE4Reference, uintptr_t> functionPtrs;  // Looked up addresses
        std::map<UE4Reference, Hook*> hooks;            // enabled hooks

        FUObjectArray *GUObjectArray;
        TNameEntryArray* GNames;
        UEngine* GEngine; // Just get from GUObjectArray?

    };

    // For internal use, but I guess I'll work that out later..
    //namespace {
    extern Data data;
    //}

    Data *Init(std::map<UE4Reference, std::string> functionPatterns);
    bool initVars();
    uintptr_t AddFunctionRef(UE4Reference refName, std::string pattern);
    uintptr_t GetFunctionRef(const UE4Reference refName);
    template<typename T>
    T GetFunction(const UE4Reference refName) {
        return (T)data.functionPtrs[refName];
    }

    bool HookFunctionRef(UE4Reference refName, const void *detour, void **original);
    bool UnhookFunctionRef(UE4Reference refName);
    bool EnableConsole(std::function<void (bool result)> fnResult);

}