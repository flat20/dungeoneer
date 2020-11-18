#pragma once
#include <diet-ue.h>
#include <unrealspy.h>

namespace spy {
    //FObjectIterator *__fastcall FObjectIterator::FObjectIterator(FObjectIterator *__hidden this, struct UClass *, bool, enum EObjectFlags, enum EInternalObjectFlags)
    //__int64 *__fastcall FObjectIterator::FObjectIterator(__int64 *a1, __int64 a2, char a3, int a4, int a5)
    typedef FObjectIterator* (__fastcall *tFObjectIterator_Ctor)(void *_this, UClass* InClass, bool bOnlyGCedObjects, EObjectFlags AdditionalExclusionFlags, EInternalObjectFlags InInternalExclusionFlags);
    typedef FNameEntry* (__fastcall *tFName_GetEntry)(FNameEntryId Id);

//	typedef unsigned int FName::ToString(FName *__hidden this, wchar_t *, unsigned int)
	typedef uint32 (__fastcall *tFName_ToString)(FName *_this, TCHAR* Out, uint32 OutSize);

	// namespace functions {
	// 	static Function<UObject* (__fastcall *)(UClass* Class, UObject* InOuter, FName Name, EObjectFlags SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype)> RefStaticConstructObject_Internal("4C 89 44 24 18 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 48 FF FF FF 48 81 EC B8 01 00 00");
    //     static Function<void (__thiscall *)(UConsole *thisUConsole, const FString *Command)> RefUConsole_ConsoleCommand("48 89 5C 24 10 48 89 6C 24 18 56 57 41 56 48 83 EC 30 83 7A 08 00 48 8D");
	// }

    extern FUObjectArray *GUObjectArray;
    // extern TNameEntryArray *GNames;
    extern UEngine* GEngine;
	bool initVars();


    // Slightly changed from 4.22 although maybe 4.22 could use this too?
	class FRawObjectIterator : public FUObjectArray::TIterator
	{
	public:
		FRawObjectIterator( bool bOnlyGCedObjects = false ) : 
            FUObjectArray::TIterator(*GUObjectArray, bOnlyGCedObjects)
		{
		}

		/**
		 * Iterator dereference
		 * @return	the object pointer pointed at by the iterator
		 */
		FORCEINLINE ::UObject* operator*() const
		{
            // casting UObjectBase to UObject for clients
            FUObjectItem* ObjectItem = GetObject();
            return (UObject*)(ObjectItem ? ObjectItem->Object : nullptr);
		}
		/**
		 * Iterator dereference
		 * @return	the object pointer pointed at by the iterator
		 */
        FORCEINLINE ::UObject* operator->() const
        {
            FUObjectItem* ObjectItem = GetObject();
            return (UObject*)(ObjectItem ? ObjectItem->Object : nullptr);
        }
	};

}