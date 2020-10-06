Allocates a Class
qword_142D0D270 = FUObjectAllocator::AllocateUObject(
                        (FUObjectAllocator *)&GUObjectAllocator,
                        512,
                        (unsigned int)((_DWORD)qword_142D0D270 + 8),
                        1);
Ustruct 512 bytes big.

UClass::UClass ctor

    v11 = a1;
  calls UStruct::UStruct(a1, 0i64, a4, a8);
  *(_QWORD *)v11 = &UClass::`vftable';
  *(_QWORD *)(v11 + 152) = a9;
  *(_QWORD *)(v11 + 160) = a10;
  *(_QWORD *)(v11 + 168) = a11;
  *(_DWORD *)(v11 + 176) = 0;
  *(_DWORD *)(v11 + 180) = a5 | 0x80;
  *(_QWORD *)(v11 + 184) = a6;
  *(_QWORD *)(v11 + 192) = 0i64;
  *(_QWORD *)(v11 + 200) = 0i64;
  *(_QWORD *)(v11 + 208) = 0i64;
  *(_QWORD *)(v11 + 216) = 0i64;
  *(_QWORD *)(v11 + 224) = 0i64;
  *(_QWORD *)(v11 + 232) = 0i64;
  *(_QWORD *)(v11 + 240) = 0i64;
  *(_QWORD *)(v11 + 248) = 0i64;
  *(_QWORD *)(v11 + 256) = 0i64;
  *(_QWORD *)(v11 + 264) = 0i64;
  *(_QWORD *)(v11 + 288) = 0i64;
  *(_QWORD *)(v11 + 296) = 0i64;
  *(_DWORD *)(v11 + 304) = -1;
  *(_DWORD *)(v11 + 308) = 0;
  *(_QWORD *)(v11 + 320) = 0i64;
  *(_DWORD *)(v11 + 328) = 0;
  *(_QWORD *)(v11 + 336) = 0i64;
  *(_QWORD *)(v11 + 344) = 0i64;
  *(_QWORD *)(v11 + 368) = 0i64;
  *(_QWORD *)(v11 + 376) = 0i64;
  *(_DWORD *)(v11 + 384) = -1;
  *(_DWORD *)(v11 + 388) = 0;
  *(_QWORD *)(v11 + 400) = 0i64;
  *(_DWORD *)(v11 + 408) = 0;
  InitializeSRWLock((PSRWLOCK)(v11 + 416));
  *(_QWORD *)(v11 + 424) = 0i64;
  *(_QWORD *)(v11 + 432) = 0i64;
  *(_QWORD *)(v11 + 440) = 0i64;
  *(_QWORD *)(v11 + 448) = 0i64;
  InitializeCriticalSection((LPCRITICAL_SECTION)(v11 + 456));
  SetCriticalSectionSpinCount((LPCRITICAL_SECTION)(v11 + 456), 0xFA0u);
  *(_QWORD *)(v11 + 496) = 0i64;
  *(_QWORD *)(v11 + 504) = 0i64;
  *(_QWORD *)(v11 + 208) = a7;

  UStruct( EStaticConstructor, int32 InSize, EObjectFlags InFlags );

  __int64 __fastcall UStruct::UStruct(__int64 a1, __int64 a2, int InSize, unsigned int flags)
{
  int v4InSize; // ebx
  __int64 v5; // rdi
  __int64 result; // rax

  v4InSize = InSize;
  v5 = a1;
  UObject::UObject(a1, 0i64, flags);
  *(_QWORD *)v5 = &UStruct::`vftable';
  result = v5;
  *(_QWORD *)(v5 + 40) = 0i64; // This should be the UField::Next !?
  *(_QWORD *)(v5 + 48) = 0i64;  // StructBaseChainArray
  *(_DWORD *)(v5 + 56) = -1; // NumStructBasesInChainMinusOne
  *(_QWORD *)(v5 + 64) = 0i64; // SuperStruct
  *(_QWORD *)(v5 + 72) = 0i64; // Children
  *(_DWORD *)(v5 + 80) = v4InSize; // PropertiesSize
  *(_DWORD *)(v5 + 84) = 1;   //  MinAlignment
  *(_QWORD *)(v5 + 88) = 0i64;
  *(_QWORD *)(v5 + 96) = 0i64;
  *(_QWORD *)(v5 + 104) = 0i64; // This is looped when finding a property by name
  *(_QWORD *)(v5 + 112) = 0i64;
  *(_QWORD *)(v5 + 120) = 0i64;
  *(_QWORD *)(v5 + 128) = 0i64;
  *(_QWORD *)(v5 + 136) = 0i64;
  *(_QWORD *)(v5 + 144) = 0i64;
  return result;
}

// #STR: "We are currently retrieving VTable ptr. Please use FVTable, "We are currently retrieving VTable ptr. Please use FVTable, "Unknown"
_QWORD *__fastcall UObject::UObject(_QWORD *a1, __int64 a2, unsigned int a3)
{
  _QWORD *v3; // rbx

  v3 = a1;
  UObjectBase::UObjectBase(a1, a3 | ((~(a3 >> 26) & 1) != 0 ? 0x84 : 0));
  *v3 = &UReverbPluginSourceSettingsBase::`vftable';
  if ( GIsRetrievingVTablePtr )
  {
    LowLevelFatalErrorHandler(
      "Unknown",
      98,
      L"We are currently retrieving VTable ptr. Please use FVTableHelper constructor instead.");
    FDebug::AssertFailed(
      &Source,
      "Unknown",
      98,
      L"We are currently retrieving VTable ptr. Please use FVTableHelper constructor instead.");
  }
  return v3;
}

__int64 __fastcall UObjectBase::UObjectBase(__int64 a1, int a2)
{
  *(_DWORD *)(a1 + 8) = a2; // ObjectFlags
  *(_QWORD *)a1 = &UObjectBase::`vftable';
  *(_QWORD *)(a1 + 16) = 0i64; // ClassPrivate
  *(_DWORD *)(a1 + 12) = -1; // InternalIndex
  *(_QWORD *)(a1 + 24) = 0i64; // NamePrivate
  *(_QWORD *)(a1 + 32) = 0i64; // OuterPrivate
  return a1;
}

UFunction + 98h = EFunctionFlags
DWORD +0a2h  162
QWORD +0a8 168
QWORD +0b0h 176
DWORD +0b8h 184

UClass( EStaticConstructor, FName InName, uint32 InSize, EClassFlags InClassFlags, EClassCastFlags InClassCastFlags,
		const TCHAR* InClassConfigName, EObjectFlags InFlags, ClassConstructorType InClassConstructor,
		ClassVTableHelperCtorCallerType InClassVTableHelperCtorCaller,
		ClassAddReferencedObjectsType InClassAddReferencedObjects);

public: UClass::UClass(enum  EStaticConstructor, class FName, unsigned int, enum  EClassFlags, enum  EClassCastFlags,
 wchar_t const *, enum  EObjectFlags, void (*)(class FObjectInitializer const &),
  class UObject * (*)(class FVTableHelper &), 
  void (*)(class UObject *, class FReferenceCollector &))

__int64 __fastcall UClass::UClass(__int64 a1,
 __int64 a2, __int64 a3, unsigned int a4, int a5, __int64 a6,
  __int64 a7, unsigned int a8, __int64 a9,
   __int64 a10, 
   __int64 a11)
{
  __int64 v11; // rdi

  v11 = a1;
  UStruct::UStruct(a1, 0i64, a4, a8);
  *(_QWORD *)v11 = &UClass::`vftable';
  *(_QWORD *)(v11 + 152) = a9;
  *(_QWORD *)(v11 + 160) = a10;
  *(_QWORD *)(v11 + 168) = a11;
  *(_DWORD *)(v11 + 176) = 0;
  *(_DWORD *)(v11 + 180) = a5 | 0x80;
  *(_QWORD *)(v11 + 184) = a6; // ClassCastFlags
  *(_QWORD *)(v11 + 192) = 0i64;
  *(_QWORD *)(v11 + 200) = 0i64;
  *(_QWORD *)(v11 + 208) = 0i64;
  *(_QWORD *)(v11 + 216) = 0i64;
  *(_QWORD *)(v11 + 224) = 0i64;
  *(_QWORD *)(v11 + 232) = 0i64;
  *(_QWORD *)(v11 + 240) = 0i64;
  *(_QWORD *)(v11 + 248) = 0i64;
  *(_QWORD *)(v11 + 256) = 0i64;
  *(_QWORD *)(v11 + 264) = 0i64;
  *(_QWORD *)(v11 + 288) = 0i64;
  *(_QWORD *)(v11 + 296) = 0i64;
  *(_DWORD *)(v11 + 304) = -1;
  *(_DWORD *)(v11 + 308) = 0;
  *(_QWORD *)(v11 + 320) = 0i64;
  *(_DWORD *)(v11 + 328) = 0;
  *(_QWORD *)(v11 + 336) = 0i64;
  *(_QWORD *)(v11 + 344) = 0i64;
  *(_QWORD *)(v11 + 368) = 0i64;
  *(_QWORD *)(v11 + 376) = 0i64;
  *(_DWORD *)(v11 + 384) = -1;
  *(_DWORD *)(v11 + 388) = 0;
  *(_QWORD *)(v11 + 400) = 0i64;
  *(_DWORD *)(v11 + 408) = 0;
  InitializeSRWLock((PSRWLOCK)(v11 + 416));
  *(_QWORD *)(v11 + 424) = 0i64;
  *(_QWORD *)(v11 + 432) = 0i64;
  *(_QWORD *)(v11 + 440) = 0i64;
  *(_QWORD *)(v11 + 448) = 0i64;
  InitializeCriticalSection((LPCRITICAL_SECTION)(v11 + 456));
  SetCriticalSectionSpinCount((LPCRITICAL_SECTION)(v11 + 456), 0xFA0u);
  *(_QWORD *)(v11 + 496) = 0i64;
  *(_QWORD *)(v11 + 504) = 0i64;
  *(_QWORD *)(v11 + 208) = a7;
  return v11;
}