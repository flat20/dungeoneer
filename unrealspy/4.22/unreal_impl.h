#pragma once
#include <diet-ue.h>
#include "../unrealspy.h"
#include "../functions.h"


namespace spy {

	namespace functions {
		// Specific for 4.22 - Move later.
		typedef TNameEntryArray& (__stdcall *tFName_GetNames)();
		extern FunctionAddr<tFName_GetNames> FName_GetNames;
		typedef ::FRawObjectIterator* (__thiscall *tFRawObjectIterator)(void *_this, bool bOnlyGCedObjects);
		extern FunctionAddr<tFRawObjectIterator> FRawObjectIterator;
        typedef UObject* (__fastcall *tStaticConstructObject_Internal)(UClass* Class, UObject* InOuter, FName Name, EObjectFlags SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype);
        extern FunctionAddr<tStaticConstructObject_Internal> StaticConstructObject_Internal;
        typedef void (__thiscall *tUConsole_ConsoleCommand)(UConsole *thisUConsole, const FString *Command);
        extern FunctionAddr<tUConsole_ConsoleCommand> UConsole_ConsoleCommand;

	}
}

namespace spy {

	//typedef TNameEntryArray& (__stdcall *tFName_GetNames) ();
	//typedef FRawObjectIterator* (__thiscall *tFRawObjectIterator_Ctor)(void *_this, bool bOnlyGCedObjects);



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

}