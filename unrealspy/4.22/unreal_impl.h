#pragma once
#include <diet-ue.h>

namespace spy {

	typedef TNameEntryArray& (__stdcall *tFName_GetNames) ();
	typedef FRawObjectIterator* (__thiscall *tFRawObjectIterator_Ctor)(void *_this, bool bOnlyGCedObjects);

    extern FUObjectArray *GUObjectArray;
    extern TNameEntryArray *GNames;
    extern UEngine* GEngine;

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
		FORCEINLINE ::FUObjectItem* operator*() const
		{
			// casting UObjectBase to UObject for clients
			return GetObject();
		}
		/**
		 * Iterator dereference
		 * @return	the object pointer pointed at by the iterator
		 */
		FORCEINLINE ::FUObjectItem* operator->() const
		{
			return GetObject();
		}
	};

}