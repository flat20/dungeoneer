#pragma once
#include <diet-ue.h>

namespace spy {

	typedef TNameEntryArray& (__stdcall *tFName_GetNames) ();
	typedef FRawObjectIterator* (__thiscall *tFRawObjectIterator_Ctor)(void *_this, bool bOnlyGCedObjects);

    extern FUObjectArray *GUObjectArray;
    extern TNameEntryArray *GNames;
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

	// class FRawObjectIterator : public FUObjectArray::TIterator
	// {
	// public:
	// 	FRawObjectIterator( bool bOnlyGCedObjects = false ) : 
    //         FUObjectArray::TIterator(*GUObjectArray, bOnlyGCedObjects)
	// 	{
	// 	}

	// 	/**
	// 	 * Iterator dereference
	// 	 * @return	the object pointer pointed at by the iterator
	// 	 */
	// 	FORCEINLINE ::FUObjectItem* operator*() const
	// 	{
	// 		// casting UObjectBase to UObject for clients
	// 		return GetObject();
	// 	}
	// 	/**
	// 	 * Iterator dereference
	// 	 * @return	the object pointer pointed at by the iterator
	// 	 */
	// 	FORCEINLINE ::FUObjectItem* operator->() const
	// 	{
	// 		return GetObject();
	// 	}
	// };

}