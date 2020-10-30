#pragma once

// Only included so my IDE stops complaining. /FI included at compile time anyway
#include "defines.h"

// Core stuff
#include <UObject\Object.h>
#include <UObject\Class.h>
#include <HAL\ConsoleManager.h>
#include <UObject\UObjectArray.h>
#include <UObject\UObjectIterator.h>
//#include <HAL\UnrealMemory.h>

// Not core
#include <Engine\World.h>

//#include <Engine\World.h>
// Try just this one?
//D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Public\CoreMinimal.h
// UE SDK has generated .h files.
// D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\
//



class UFont : UObject {

};

class UConsole : UObject {
};




namespace diet {
	class FRawObjectIterator : public FUObjectArray::TIterator
	{
	public:
		FRawObjectIterator( const FUObjectArray& InArray, bool bOnlyGCedObjects = false ) : FUObjectArray::TIterator(InArray, bOnlyGCedObjects)
		{
		}

		/**
		 * Iterator dereference
		 * @return	the object pointer pointed at by the iterator
		 */
		FORCEINLINE FUObjectItem* operator*() const
		{
			// casting UObjectBase to UObject for clients
			return GetObject();
		}
		/**
		 * Iterator dereference
		 * @return	the object pointer pointed at by the iterator
		 */
		FORCEINLINE FUObjectItem* operator->() const
		{
			return GetObject();
		}
	};

	// Rename or make inner somewhere. Just to speed things up
	// when finding names.
	class FNameEntry : public ::FNameEntry {
	public:
		void *GetPtr()
		{
			//if (IsWide()) {
			//	return &WideName[0];
			//} else {
				return &AnsiName[0];
			//} 
		}
	};
}
