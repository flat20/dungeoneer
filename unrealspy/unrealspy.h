#pragma once
#include "unreal.h"


typedef signed int (__thiscall *tProcessEvent) (UObject* object, UFunction* func, void *params);
typedef void (__thiscall *tPostRender) (void *hud);
typedef TNameEntryArray* (__stdcall *FName_GetNames) ();
//typedef FRawObjectIterator *__fastcall FRawObjectIteratorCtor(FRawObjectIterator *this, bool bOnlyGCedObjects);
typedef void* (__thiscall *FRawObjectIterator_Ctor)(void *_this, bool bOnlyGCedObjects);

// void __stdcall __high AHUD::DrawRect(struct FLinearColor, float, float, float, float)
typedef void (__thiscall *AHUD_DrawRect)(void *hud, FLinearColor RectColor, float ScreenX, float ScreenY, float ScreenW, float ScreenH);

// void __stdcall __high AHUD::DrawText(const struct FString *, struct FLinearColor, float, float, struct UFont *, float, bool)
// 	void DrawText(const FString& Text, FLinearColor TextColor, float ScreenX, float ScreenY, UFont* Font=NULL, float Scale=1.f, bool bScalePosition=false);
typedef void (__thiscall *AHUD_DrawText)(void *hud, const FString* Text, FLinearColor TextColor, float ScreenX, float ScreenY, UFont* Font, float Scale, bool bScalePosition);

// Sadly does not take linebreaks in to account so no good for multiline, if we care about that.
//void __fastcall AHUD::GetTextSize(AHUD *__hidden this, const struct FString *, float *, float *, struct UFont *, float)
typedef void (__thiscall *AHUD_GetTextSize)(void *hud, const FString* Text, float* OutWidth, float* OutHeight, UFont* Font, float Scale);

//  UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr, bool bAllowObjectReconciliation = true, FUObjectSerializeContext* InSerializeContext = nullptr );
// _int64 __fastcall StaticLoadObject(struct UClass *a1, struct UObject *a2, const wchar_t *a3, const wchar_t *a4, unsigned int a5, struct UPackageMap *a6, bool a7, struct FUObjectSerializeContext *a8)
typedef UObject* (__fastcall *StaticLoadObject)(UClass* Class, UObject* Inouter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, void* Sandbox, bool bAllowObjectReconciliation, void *InSerializeContext);

// COREUOBJECT_API UClass* StaticLoadClass(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr);
typedef UClass* (__fastcall *StaticLoadClass)(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, void* Sandbox);

// COREUOBJECT_API UPackage* LoadPackage( UPackage* InOuter, const TCHAR* InLongPackageName, uint32 LoadFlags, FArchive* InReaderOverride = nullptr, FUObjectSerializeContext* InLoadContext = nullptr );
typedef UPackage* (__fastcall *LoadPackage)( UPackage* InOuter, const TCHAR* InLongPackageName, uint32 LoadFlags, void* InReaderOverride, void* InLoadContext );


// We need global access to some predefined functions and names.
// Can't use string enums so maybe this?
typedef std::string UE4Reference;
const UE4Reference RefUObject_ProcessEvent      = "UObject_ProcessEvent";
const UE4Reference RefAHUD_PostRender           = "AHUD_PostRender";
const UE4Reference RefFName_GetNames            = "FName_GetNames";
const UE4Reference RefFRawObjectIterator_Ctor   = "FRawObjectIterator_Ctor";
const UE4Reference RefStaticLoadObject          = "StaticLoadObject";
const UE4Reference RefStaticLoadClass           = "StaticLoadClass";
const UE4Reference RefLoadPackage               = "LoadPackage";

struct SpyData {
    uint64 baseAddress;             // Base address of process
    FUObjectArray *GUObjectArray;
    TNameEntryArray* GNames;
    //UEngine* GEngine; // Just get from GUObjectArray?

    AHUD_DrawRect AHUD_DrawRect;
    AHUD_DrawText AHUD_DrawText;
    AHUD_GetTextSize AHUD_GetTextSize;
    StaticLoadObject StaticLoadObject;
    StaticLoadClass StaticLoadClass;
    LoadPackage LoadPackage;
    FName_GetNames FName_GetNames;
    FRawObjectIterator_Ctor FRawObjectIterator_Ctor;

    tProcessEvent origProcessEvent = NULL;
    void *detourProcessEvent = NULL;
    tPostRender origPostRender = NULL;
    void *detourPostRender = NULL;

    // GetNames returns pointer to GNames array, I think.
    // tGetNames origGetNames = nullptr;
    // void *detourGetNames = nullptr;
};

// Give a list of these to SpyData to hook them.
struct SpyHook {
    // Offset in process
    uint64 offset;
    // Replace original with this
    void *detourFunction;
    // Pointer to the original function
    void *origFunction;
};



// Hook everything up, pass in offsets.
bool InitSpy(SpyData*, std::map<UE4Reference, uintptr_t> addresses);
bool DeInitSpy(SpyData*);