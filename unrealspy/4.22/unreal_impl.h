#pragma once
#include <diet-ue.h>
#include <unrealspy.h>
#include "../offsets.h"


namespace offsets {
	namespace functions {
		// Should be defined in unrealspy. Probably FunctionAddress should be defined in unrealspy too.
		// Any shared functions between SDKs here. Others in unrealspy/4.X/offsets.h
		// Can't put it there due to circular #include issues.
		// Templated subclass with Call which makes it look
		// and feel almost like a real function when using.
		template<typename T>
		class FunctionAddr : public ::offsets::OpcodeAddress {
		public:

			FunctionAddr(const char *InOpcodes) : OpcodeAddress(InOpcodes)
			{        
			}

			// Needed 
			void SetAddress(uintptr_t Address) override {
				::offsets::OpcodeAddress::SetAddress(Address);
				Call = (T)Address;
			}

			// Ref to function, named Call for neater calling code later.
			T Call;

		};

		// Specific for 4.22
		extern FunctionAddr<TNameEntryArray& (__stdcall *)()> FName_GetNames;
		extern FunctionAddr<::FRawObjectIterator* (__thiscall *)(void *_this, bool bOnlyGCedObjects)> FRawObjectIterator;

		extern FunctionAddr<UObject* (__fastcall *)(UClass* Class, UObject* InOuter, FName Name, EObjectFlags SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype)> StaticConstructObject_Internal;
		extern FunctionAddr<void (__thiscall *)(UConsole *thisUConsole, const FString *Command)> UConsole_ConsoleCommand;
		extern FunctionAddr<signed int (__thiscall *)(UObject* thisObject, UFunction* func, void *params)> UObject_ProcessEvent;
		extern FunctionAddr<signed int (__thiscall *) (AActor* thisActor, UFunction* func, void *params)> AActor_ProcessEvent;
		typedef void (__thiscall *tAHUD_PostRender) (void *hud);
		extern FunctionAddr<tAHUD_PostRender> AHUD_PostRender;


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