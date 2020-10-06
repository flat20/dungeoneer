
TODO - There are subclasses of UProperty.
Perhaps if we find a property, we look at its UObject.ClassPrivate.ClassCastFlags
and check what type it is?
UFloatProperty actually inherits from
	public TProperty_Numeric<float> which inherits from
		TProperty_WithEqualityAndSerializer<InTCppType, UNumericProperty>

		GetFloatingPointPropertyValue(void *Data) does this in asm:
			F3 0F 10 02                                   movss   xmm0, dword ptr [rdx]
.text:00000001406C7524 0F 5A C0                           cvtps2pd xmm0, xmm0
.text:00000001406C7527 C3                                 retn
		Should be easy enough in regular C?



void UIllusionToolkit::SetFloats(UObject* Object, FName PropertyName, float PropertyValue)
{
	UProperty* Property = Object->GetClass()->FindPropertyByName(PropertyName);

	if (UNumericProperty *NumericProperty = Cast<UNumericProperty>(Property))
	{
		if (UFloatProperty *FloatProperty = Cast<UFloatProperty>(NumericProperty))
		{
			void* ValuePtr = FloatProperty->ContainerPtrToValuePtr<void>(Object);
			FloatProperty->SetFloatingPointPropertyValue(ValuePtr, PropertyValue);
		}

	}
}

    UnrealTypes.h class UProperty
	/** 
	 *	Get the pointer to property value in a supplied 'container'. 
	 *	You can _only_ call this function on a UObject* or a uint8*. If the property you want is a 'top level' UObject property, you _must_
	 *	call the function passing in a UObject* and not a uint8*. There are checks inside the function to vertify this.
	 *	@param	ContainerPtr			UObject* or uint8* to container of property value
	 *	@param	ArrayIndex				In array case, index of array element we want
	 */
	template<typename ValueType>
	FORCEINLINE ValueType* ContainerPtrToValuePtr(UObject* ContainerPtr, int32 ArrayIndex = 0) const
	{
		return (ValueType*)ContainerUObjectPtrToValuePtrInternal(ContainerPtr, ArrayIndex);
	}


	FORCEINLINE void* ContainerUObjectPtrToValuePtrInternal(UObject* ContainerPtr, int32 ArrayIndex) const
	{
		check(ArrayIndex < ArrayDim);
		check(ContainerPtr);

		// in the future, these checks will be tested if the property is supposed be from a UClass
		// need something for networking, since those are NOT live uobjects, just memory blocks
		check(((UObject*)ContainerPtr)->IsValidLowLevel()); // Check its a valid UObject that was passed in
		check(((UObject*)ContainerPtr)->GetClass() != NULL);
		check(GetOuter()->IsA(UClass::StaticClass())); // Check that the outer of this property is a UClass (not another property)

		// Check that the object we are accessing is of the class that contains this property
		checkf(((UObject*)ContainerPtr)->IsA((UClass*)GetOuter()), TEXT("'%s' is of class '%s' however property '%s' belongs to class '%s'")
			, *((UObject*)ContainerPtr)->GetName()
			, *((UObject*)ContainerPtr)->GetClass()->GetName()
			, *GetName()
			, *((UClass*)GetOuter())->GetName());

		if (0)
		{
			// in the future, these checks will be tested if the property is NOT relative to a UClass
			check(!GetOuter()->IsA(UClass::StaticClass())); // Check we are _not_ calling this on a direct child property of a UClass, you should pass in a UObject* in that case
		}

		return (uint8*)ContainerPtr + Offset_Internal + ElementSize * ArrayIndex;
	}

    so UObject has have ClassPrivate != null
    UObject::OuterPrivate has to be a UClass
    Then check if UObject::ClassPrivate::Name matches UProperty::GetOuter()::GetName
    They are calling GetName() to get the property name. That never works for me. UProperty struct bugged?
    Finally:
    return (uint8*)ContainerPtr + Offset_Internal + ElementSize * ArrayIndex;
    ArrayIndex is only for array elements


    In UObject::
	/** Returns the UClass that defines the fields of this object */
	FORCEINLINE UClass* GetClass() const
	{
		return ClassPrivate;
	}

    

	/** 
	 * Gets the value of an floating point property type
	 * @param Data - pointer to property data to get
	 * @return Data as a double
	**/
	virtual double GetFloatingPointPropertyValue(void const* Data) const;


    FindPropertyByName
    
    In UStruct.
    result = this+104
    if (result == 0) {
        return 0;
    }
    if (result+24.Index == fname.Index or result+24.Name == fname.Name)  { maybe the other way around
        result = result+80; // UProperty
        if 
    }
    If this+104 == 0, return 0
    if 
    __int64 __fastcall UStruct::FindPropertyByName(__int64 a1, __int64 a2)
{
  __int64 result; // rax

  result = *(_QWORD *)(a1 + 104);
  if ( !result )
    return 0i64;
  while ( *(_QWORD *)(result + 24) >> 32 != HIDWORD(a2) || (unsigned int)*(_QWORD *)(result + 24) != (_DWORD)a2 )
  {
    result = *(_QWORD *)(result + 80);
    if ( !result )
      return 0i64;
  }
  return result;
}

https://answers.unrealengine.com/questions/212756/setget-uproperty-inside-of-ustruct-directly.html
     FName PropName = FName("MyVector");
     FName VectorMemberName = FName("X");
     float NewValue = 42.0;
     
     // Get property representing struct
     UProperty * Prop = ObjectWithVector->GetClass()->FindPropertyByName(PropName);
     
     // Ensure ObjectWithVector actually has a myVector member
     if (Prop)
     {
         // Get struct address
         void * StructAddress = Prop->ContainerPtrToValuePtr<void>(ObjectWithVector);
         
         // Ensure MyVector really is a vector
         if (UStructProperty * StructProp = Cast<UStructProperty>(Prop))
         {
             // We'll get struct properties through a UScriptStruct, not a UObject
             // ScriptStructs are just templates and don't hold any of your data
             UScriptStruct * ScriptStruct = StructProp->Struct;
             

             // Get the vector's "X" property
             UProperty * ChildProp = ScriptStruct->FindPropertyByName(VectorMemberName);
 
             // Cast to FloatProperty
             if (UFloatProperty * ChildFloatProp = Cast<UFloatProperty>(ChildProp))
             {
                 // Get
                 float OldValue = ChildFloatProp->GetFloatingPointPropertyValue(StructAddress);
                 
                 // Set
                 ChildFloatProp->SetFloatingPointPropertyValue(StructAddress, NewValue);
                 
                 return OldValue;
             }
			
		UStructProperty* NodeProperty = AnimBlueprintClass->GetAnimNodeProperties()[AnimBlueprintClass->GetAnimNodeProperties().Num() - 1 - PropertyIndex]; //@TODO: Crazysauce
		check(NodeProperty->Struct == NodeType::StaticStruct());
		return NodeProperty->ContainerPtrToValuePtr<NodeType>(AnimInstanceObject);
		ContainerUObjectPtrToValuePtrInternal
		So we need to call 

		GetPropertyValue is a good one to search for, for most properties.