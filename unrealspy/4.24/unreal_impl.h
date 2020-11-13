#pragma once
#include <diet-ue.h>

namespace spy {
    //FObjectIterator *__fastcall FObjectIterator::FObjectIterator(FObjectIterator *__hidden this, struct UClass *, bool, enum EObjectFlags, enum EInternalObjectFlags)
    //__int64 *__fastcall FObjectIterator::FObjectIterator(__int64 *a1, __int64 a2, char a3, int a4, int a5)
    typedef FObjectIterator* (__fastcall *tFObjectIterator_Ctor)(void *_this, UClass* InClass, bool bOnlyGCedObjects, EObjectFlags AdditionalExclusionFlags, EInternalObjectFlags InInternalExclusionFlags);
    typedef FNameEntry* (__fastcall *tFName_GetEntry)(FNameEntryId Id);

//	typedef unsigned int FName::ToString(FName *__hidden this, wchar_t *, unsigned int)
	typedef uint32 (__fastcall *tFName_ToString)(FName *_this, TCHAR* Out, uint32 OutSize);


    extern FUObjectArray *GUObjectArray;
    // extern TNameEntryArray *GNames;
    extern UEngine* GEngine;

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