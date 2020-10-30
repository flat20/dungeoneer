#pragma once
#include "unreal.h"

/** TFieldIterator construction flags */
namespace EFieldIteratorFlags
{
	enum SuperClassFlags
	{
		ExcludeSuper = 0,	// Exclude super class
		IncludeSuper		// Include super class
	};

	enum DeprecatedPropertyFlags
	{
		ExcludeDeprecated = 0,	// Exclude deprecated properties
		IncludeDeprecated		// Include deprecated properties
	};

	enum InterfaceClassFlags
	{
		ExcludeInterfaces = 0,	// Exclude interfaces
		IncludeInterfaces		// Include interfaces
	};
}

//
// For iterating through a linked list of fields.
//
template <class T>
class TFieldIterator
{
private:
	/** The object being searched for the specified field */
	const UStruct* Struct;
	/** The current location in the list of fields being iterated */
	UField* Field;
	/** The index of the current interface being iterated */                             
	int32 InterfaceIndex;
	/** Whether to include the super class or not */
	const bool bIncludeSuper;
	/** Whether to include deprecated fields or not */
	const bool bIncludeDeprecated;
	/** Whether to include interface fields or not */
	const bool bIncludeInterface;

public:
	TFieldIterator(const UStruct*                               InStruct,
	               EFieldIteratorFlags::SuperClassFlags         InSuperClassFlags      = EFieldIteratorFlags::IncludeSuper,
	               EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedFieldFlags = EFieldIteratorFlags::IncludeDeprecated,
	               EFieldIteratorFlags::InterfaceClassFlags     InInterfaceFieldFlags  = EFieldIteratorFlags::IncludeInterfaces)
		: Struct            ( InStruct )
		, Field             ( InStruct ? InStruct->Children : NULL )
		, InterfaceIndex    ( -1 )
		, bIncludeSuper     ( InSuperClassFlags      == EFieldIteratorFlags::IncludeSuper )
		, bIncludeDeprecated( InDeprecatedFieldFlags == EFieldIteratorFlags::IncludeDeprecated )
		, bIncludeInterface ( InInterfaceFieldFlags  == EFieldIteratorFlags::IncludeInterfaces )//&& InStruct && InStruct->IsA(UClass::StaticClass()) )
	{
		IterateToNext();
	}

	/** conversion to "bool" returning true if the iterator is valid. */
	inline explicit operator bool() const
	{ 
		return Field != NULL; 
	}
	/** inverse of the "bool" operator */
	inline bool operator !() const 
	{
		return !(bool)*this;
	}

	inline friend bool operator==(const TFieldIterator<T>& Lhs, const TFieldIterator<T>& Rhs) { return Lhs.Field == Rhs.Field; }
	inline friend bool operator!=(const TFieldIterator<T>& Lhs, const TFieldIterator<T>& Rhs) { return Lhs.Field != Rhs.Field; }

	inline void operator++()
	{
		// checkSlow(Field);
		Field = Field->Next;
		IterateToNext();
	}
	inline T* operator*()
	{
		// checkSlow(Field);
		return (T*)Field;
	}
	inline T* operator->()
	{
		// checkSlow(Field);
		return (T*)Field;
	}
	inline const UStruct* GetStruct()
	{
		return Struct;
	}
protected:
	inline void IterateToNext()
	{
		      UField*  CurrentField  = Field;
		const UStruct* CurrentStruct = Struct;
		while (CurrentStruct)
		{
			while (CurrentField)
			{
				//UClass* FieldClass = CurrentField->ClassPrivate;

                // If class of field is the class we're after or it's a property, return it.
                // But we don't have a good set of flags to check for each class.
                // In fact for UIntProperty we don't have a class to grab the flags from
                // so perhaps one could provide them if needed.
				//if (util::HasFlags(FieldClass, (EClassCastFlags)T::StaticClassCastFlags)
                //    || util::HasFlags(FieldClass, CASTCLASS_UProperty))
                //{
					Struct = CurrentStruct;
					Field  = CurrentField;
					return;
				//}

				//CurrentField = CurrentField->Next;
			}

			// We don't know if it's a class or not
			// if (bIncludeInterface)
			// {
			// 	// We shouldn't be able to get here for non-classes
			// 	UClass* CurrentClass = (UClass*)CurrentStruct;
			// 	++InterfaceIndex;
			// 	if (InterfaceIndex < CurrentClass->Interfaces.ArrayNum)
			// 	{
			// 		FImplementedInterface& Interface = CurrentClass->Interfaces.Data[InterfaceIndex];
			// 		CurrentField = Interface.Class ? Interface.Class->Children : nullptr;
			// 		continue;
			// 	}
			// }

            // Requires a virtual function because it can be overriden by subclasses
			// So this code is not strictly correct if the object has a weird super
			if (bIncludeSuper)
			{
			 	//CurrentStruct = CurrentStruct->GetInheritanceSuper();
				CurrentStruct = CurrentStruct->SuperStruct;
			 	if (CurrentStruct)
			 	{
			 		CurrentField   = CurrentStruct->Children;
			 		InterfaceIndex = -1;
			 		continue;
			 	}
			}

			break;
		}

		Struct = CurrentStruct;
		Field  = CurrentField;
	}
};

//for (TFieldIterator<UProperty> PropIt(Obj->GetClass()); PropIt; ++PropIt)
//for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr )
//for ( TObjectIterator<USkeletalMeshComponent> Itr; Itr; ++Itr )
// for (TFieldIterator<UFunction> FunctionIt(Class, EFieldIteratorFlags::IncludeSuper); FunctionIt; ++FunctionIt)
// 	{
// 		UFunction* Function = *FunctionIt;