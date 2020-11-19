#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include <diet-ue.h>
#include <unreal_impl.h>

#include "offsets.h"

#ifdef SPYAPI_IMPORT
//    #define SPYAPI __declspec(dllimport)
#else
    #define SPYAPI __declspec(dllexport)
#endif

namespace spy {

//     // Some defaults for us.
//     std::map<UE4Reference, std::string> defaultAddressLookups = {
//         {RefFName_GetNames,                 "48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20"},
//         // Sort of Ctor for FNames. Does the main work
//         {RefFName_Init,                     "48 89 5C 24 18 55 56 57 48 81 EC 60 08 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 84 24 50 08 00 00 0F B7 02"},
//         {RefFRawObjectIterator_Ctor,        "84 D2 48 C7 41 10 00 00 00 00 B8 FF FF FF FF ?? ?? ?? ?? ?? ?? ?? 89 41 08 4C 8B D1 4C 89 01"},

//         // TODO These are UFunctions so we can just get them at runtime.
//         {"AHUD_DrawRect",                   "48 8B C4 48 89 58 08 57 48 81 EC E0 00 00 00 0F 29 70 E8 48 8B FA 0F 29 78 D8 0F 28 F3 0F 28 FA 48 8B D9"},
//         {"AHUD_DrawText",                   "40 55 56 57 48 81 EC 30 02 00 00 44 0F 29 84 24 00 02 00 00"},
//         {"AHUD_GetTextSize",                "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 40 49 8B F9 49 8B F0 48 8B EA 48 8B D9 ?? ?? ?? ?? ?? 84 C0"},

//         {RefStaticLoadObject,               "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 18 FE FF FF 48 81 EC E8 02 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 D0 01 00 00 48 8B 85 68 02 00 00"},
//         {RefStaticLoadClass,                "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 08 FF FF FF 48 81 EC F8 01 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 E0 00 00 00 8B BD 60 01 00 00"},
//         {RefLoadPackage,                    "48 8B C4 53 56 48 83 EC 68 48 89 68 08 48 8B EA 4C 89 60 18 33 D2 4C 89 68 E8 4C 8B E1 4C 89 70 E0 48 8D 48 C8 4C 89 78 D8 45 33 ED"},
//         {RefUObject_ProcessEvent,           "40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC F0 00 00 00 48 8D 6C 24 30 48 89 9D 18 01 00 00"},
//         {RefAActor_ProcessEvent,            "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B 01 49 8B F0 ?? ?? ?? ?? ?? ?? ?? 48 8B EA 48 8B D9"},
//         {RefAHUD_PostRender,                "40 55 56 48 8D 6C 24 B1 48 81 EC C8 00 00 00 48 8B 01 48 8B F1"},
// // TODO separate default offsets
// #if ENGINE_MINOR_VERSION == 22
//         {RefStaticConstructObject_Internal, "40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 50 FF FF FF 48 81 EC B0 01 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 A8 00 00 00"},
//         {RefUConsole_ConsoleCommand,        "48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 30 48 8B F2 48 89 54 24 40 48 8B D9 48 8D 54 24 40 48 83 C1 68"},
// #else
//         {RefStaticConstructObject_Internal, "4C 89 44 24 18 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 48 FF FF FF 48 81 EC B8 01 00 00"},
//         {RefUConsole_ConsoleCommand,        "48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 30 83 7A 08 00 48 8D"},
// #endif
//         {RefFConsoleManager_ProcessUserConsoleInput, "48 8B C4 4C 89 48 20 4C 89 40 18 48 89 48 08 55 56 48 8D 68 A1 48 81 EC B8 00 00 00 33 F6"},
//         //{RefAddEmeralds,                    "40 55 56 57 48 81 EC 80 00 00 00 48 C7 44 24 30 FE FF FF FF 48 89 9C 24 B0 00 00 00 0F 29 74 24 70"},
//         {RefLoadLevel,                      "40 55 53 56 57 41 56 48 8D AC 24 70 FF FF FF 48 81 EC 90 01 00 00 48 C7 44 24 70 FE FF FF FF 0F 29 B4 24 80 01 00 00"},
// //        {RefFSoftObjectPtr_LoadSynchronous, "48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B F9 ?? ?? ?? ?? ?? 33 ED 48 8B F0 48 85 C0"},
//         //{RefStaticLoadObject,               "40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 18 FE FF FF 48 81 EC E8 02 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 D0 01 00 00"},
//         {RefUWorld_SpawnActor,              "40 53 56 57 48 83 EC 70 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 44 24 60 ?? ?? ?? ?? ?? ?? ?? 0F 57 D2 48 8B B4 24 B0 00 00 00 0F 28 CB"},
//         {RefUUserWidget_CreateWidget,       "48 89 5C 24 10 48 89 74 24 18 57 48 83 EC 30 49 8B D8 48 8B FA 48 8B F1 48 85 C9 ?? ?? ?? ?? ?? ?? 48 89 6C 24 40 48 8B A9 60 01 00 00 48 85 ED"},
//         {RefUUserWidget_AddToViewport,      "48 8B 01 44 8B C2 33 D2 48 FF A0 C8 02 00 00"},
//         {RefFModuleManager_LoadModule,      "48 89 5C 24 08 57 48 83 EC 20 ?? ?? ?? ?? ?? ?? ?? 48 8B DA 48 8B F9 ?? ?? ?? ?? ?? ?? ?? ?? 4C 8D 44 24 40 48 8B D3 48 8B CF"},
//         {RefFModuleManager_LoadModuleWithFailureReason,   "48 89 54 24 10 55 53 56 57 41 54 41 55 41 56 48 8D 6C 24 D9 48 81 EC B0 00 00 00"},
//         {RefFModuleManager_Get,             "48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? ?? ?? ?? ?? 65 48 8B 04 25 58 00 00 00 8B 0D ?? ?? ?? ?? 41 B8 ?? ?? ?? ?? 48 8B 14 C8 41 8B 04 10 39 05 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 48 8D"},
//         {RefFWindowsPlatformProcess_GetDllHandle, "40 55 53 56 48 8B EC 48 83 EC 40 33 F6 48 89 7C 24 68 4C 89 7C 24 78 4C 8B F9 48 8D 4D F0"},
//         {RefUObject_CallFunctionByNameWithArguments, "40 55 53 56 57 41 54 41 55 41 56 41 57 48 81 EC F8 02 00 00 48 8D 6C 24 30"},

//         {RefFObjectIterator_Ctor,           "48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 20 44 8B 54 24 50"},
//         {RefFName_GetEntry,                 "40 53 48 83 EC 20 8B D9 0F B7 C1 C1 EB 10 ?? ?? ?? ?? ?? ?? ?? 89 5C 24 38 89 44 24 3C"},
//         {RefFName_ToString,                 "48 89 5C 24 18 48 89 74 24 20 57 48 83 EC 50 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 44 24 48 8B 01 48 8B F2"},
//     };
}

// typedef signed int (__thiscall *tUObject_ProcessEvent) (UObject* thisObject, UFunction* func, void *params);
// typedef signed int (__thiscall *tAActor_ProcessEvent) (AActor* thisActor, UFunction* func, void *params);
// typedef void (__thiscall *tAHUD_PostRender) (void *hud);

// // void __stdcall __high AHUD::DrawRect(struct FLinearColor, float, float, float, float)
// typedef void (__thiscall *tAHUD_DrawRect)(void *hud, FLinearColor RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);

// typedef void (__thiscall *tAHUD_DrawText)(void *hud, const FString* Text, FLinearColor TextColor, float ScreenX, float ScreenY, UFont* Font, float Scale, bool bScalePosition);

// // Sadly does not take linebreaks in to account so no good for multiline, if we care about that.
// //void __fastcall AHUD::GetTextSize(AHUD *__hidden this, const struct FString *, float *, float *, struct UFont *, float)
// typedef void (__thiscall *tAHUD_GetTextSize)(void *hud, const FString* Text, float* OutWidth, float* OutHeight, UFont* Font, float Scale);

// //  UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr, bool bAllowObjectReconciliation = true, FUObjectSerializeContext* InSerializeContext = nullptr );
// // _int64 __fastcall StaticLoadObject(struct UClass *a1, struct UObject *a2, const wchar_t *a3, const wchar_t *a4, unsigned int a5, struct UPackageMap *a6, bool a7, struct FUObjectSerializeContext *a8)
// typedef UObject* (__fastcall *tStaticLoadObject)(UClass* Class, UObject* Inouter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, void* Sandbox, bool bAllowObjectReconciliation, void *InSerializeContext);

// // COREUOBJECT_API UClass* StaticLoadClass(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr);
// typedef UClass* (__fastcall *tStaticLoadClass)(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, void* Sandbox);

// // COREUOBJECT_API UPackage* LoadPackage( UPackage* InOuter, const TCHAR* InLongPackageName, uint32 LoadFlags, FArchive* InReaderOverride = nullptr, FUObjectSerializeContext* InLoadContext = nullptr );
// typedef UPackage* (__fastcall *tLoadPackage)( UPackage* InOuter, const TCHAR* InLongPackageName, uint32 LoadFlags, void* InReaderOverride, void* InLoadContext );

// // COREUOBJECT_API UObject* StaticConstructObject_Internal(UClass* Class, UObject* InOuter = (UObject*)GetTransientPackage(), FName Name = NAME_None, EObjectFlags SetFlags = RF_NoFlags, EInternalObjectFlags InternalSetFlags = EInternalObjectFlags::None, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, struct FObjectInstancingGraph* InstanceGraph = nullptr, bool bAssumeTemplateIsArchetype = false);
// typedef UObject* (__fastcall *tStaticConstructObject_Internal)(UClass* Class, UObject* InOuter, FName Name, EObjectFlags SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype);
// //typedef UObject* (__fastcall *StaticConstructObject_Internal)(__int64 a1,    int a2,           __int64 a3, int a4,                int a5,                                __int64 a6,        char a7,                               __int64 a8,          char a9);

// //typedef UObject* (__thiscall *tFSoftObjectPtr_LoadSynchronous) (FSoftObjectPtr *thisSoftObjectPtr);
// 	/**
// 	 * Spawn Actors with given transform and SpawnParameters
// 	 * 
// 	 * @param	Class					Class to Spawn
// 	 * @param	Location				Location To Spawn
// 	 * @param	Rotation				Rotation To Spawn
// 	 * @param	SpawnParameters			Spawn Parameters
// 	 *
// 	 * @return	Actor that just spawned
// 	 */
//     // TODO UWorld* not UObject..
// #ifdef UE_422
// typedef AActor* (__thiscall *tUWorld_SpawnActor)( UObject* thisUWorld, UClass* InClass, FVector const* Location, FRotator const* Rotation, const FActorSpawnParameters& SpawnParameters );
// #endif

// // UUserWidget*
// typedef UObject* (__fastcall *tUUserWidget_CreateWidget)(UObject *gameInstance, UClass* cls, FName name);
// typedef UObject* (__thiscall *tUUserWidget_AddToViewport)(UObject *widget, int32 ZOrder);

// //  UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr, bool bAllowObjectReconciliation = true, FUObjectSerializeContext* InSerializeContext = nullptr );
// // struct UObject *__fastcall StaticLoadObject(struct UClass *a1, struct UObject *a2, const wchar_t *a3, const wchar_t *a4, unsigned int a5, struct UPackageMap *a6, bool a7, struct FUObjectSerializeContext *a8)
// //typedef UObject* (__fastcall *tStaticLoadObject)(UClass *Class, UObject *InOuter, const TCHAR *Name, const TCHAR* Filename, uint32 LoadFlags, void *Sandbox, bool bAllowObjectReconciliation, void *InSerializeContext);
// // IModuleInterface* LoadModule( const FName InModuleName );
// // __int64 __fastcall FModuleManager::LoadModule(__int64 a1, __int64 a2)
// typedef void* (__thiscall *tFModuleManager_LoadModule)(void *thisModuleManager, FName InModuleName);

// //__int64 __fastcall FModuleManager::LoadModuleWithFailureReason(__int64 a1, __int64 a2, _DWORD *a3)
// // IModuleInterface* FModuleManager::LoadModuleWithFailureReason(const FName InModuleName, EModuleLoadResult& OutFailureReason)
// typedef void* (__thiscall *tFModuleManager_LoadModuleWithFailureReason)(void *thisModuleManager, const FName InModuleName, uint32 &OutFailureReason);

// // FModuleManager *FModuleManager::Get(void)
// typedef void* (__fastcall *tFModuleManager_Get)();

// // void FName::Init(const WIDECHAR* InName, int32 InNumber, EFindName FindType, bool bSplitName, int32 HardcodeIndex)
// //void __stdcall __high FName::Init(const wchar_t *, int, enum EFindName, bool, int) // findType = 1, bSplitName = true, -1
// //void __fastcall FName::Init(__int64 a1, wchar_t *a2, unsigned int a3, unsigned int a4, char a5, int a6)
// typedef FName* (__stdcall *tFName_Init)(FName *thisFName, const wchar_t *InName, int32 InNumber, EFindName FindType, bool bSplitName, int32 HardcodeIndex);

// // void *__fastcall FWindowsPlatformProcess::GetDllHandle(const wchar_t *)
// // __int64 __fastcall FWindowsPlatformProcess::GetDllHandle(const wchar_t *a1)
// // void* FWindowsPlatformProcess::GetDllHandle( const TCHAR* FileName )
// typedef void* (__fastcall *tFWindowsPlatformProcess_GetDllHandle)(const TCHAR *FileName);

// // bool UObject::CallFunctionByNameWithArguments(const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec/*=false*/)

// typedef bool (__fastcall *tUobject_CallFunctionByNameWithArguments)(UObject *thisUObject, const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec);
// // We need global access to some predefined functions and names.
// // Can't use string enums so maybe this?



namespace spy {
    struct Data {
        uintptr_t baseAddress; // Base address of process, never used but let's leave for now.

    };

    // For internal use, but I guess I'll work that out later..
    //namespace {
    extern Data data;
    //}

    Data *Init();

    // uintptr_t AddFunctionRef(UE4Reference refName, std::string pattern);
    // uintptr_t GetFunctionRef(const UE4Reference refName);
    // template<typename T>
    // T GetFunction(const UE4Reference refName) {
    //     return (T)data.functionPtrs[refName];
    // }

}