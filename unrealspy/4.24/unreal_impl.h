#pragma once
#include <diet-ue.h>
#include "../unrealspy.h"
#include "../functions.h"

namespace spy {

	namespace functions {
		typedef FObjectIterator* (__fastcall *tFObjectIterator)(FObjectIterator *_this, UClass* InClass, bool bOnlyGCedObjects, EObjectFlags AdditionalExclusionFlags, EInternalObjectFlags InInternalExclusionFlags);
		extern FunctionAddr<tFObjectIterator> FObjectIterator;
        typedef UObject* (__fastcall *tStaticConstructObject_Internal)(UClass* Class, UObject* InOuter, FName Name, EObjectFlags SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype);
        extern FunctionAddr<tStaticConstructObject_Internal> StaticConstructObject_Internal;
        typedef void (__thiscall *tUConsole_ConsoleCommand)(UConsole *thisUConsole, const FString *Command);
        extern FunctionAddr<tUConsole_ConsoleCommand> UConsole_ConsoleCommand;

    	typedef FNameEntry* (__fastcall *tFName_GetEntry)(FNameEntryId Id);
		extern FunctionAddr<tFName_GetEntry> FName_GetEntry;
	}
}


namespace spy {

    extern FUObjectArray *GUObjectArray;
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