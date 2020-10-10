#pragma once
#include <functional>

#include "unreal.h"

// Anything in this namespace I'm fairly happy with, anything outside it
// is work-in-progress or stuff I needed when testing
// TODO Casing to match UE4 sdk
namespace util {

    extern TNameEntryArray* GNames;
    extern FUObjectArray* GUObjectArray;

    char * getName(FName name);
    char * getName(UObject *Object);
    
    // Return true to stop iterating.
    //void iterate(UObject *baseObject, std::function<bool (UProperty*)> fnDone);
    
    void IterateFields(UStruct *strct, std::function<bool (UField*)> fnDone);
    void IterateFields(UArrayProperty *ap, std::function<bool (UField*)> fnDone);

    template <typename T>
    void IterateProperties(T *Object, std::function<bool (UProperty*)> fnDone);
//    void IterateProperties(UStruct *strct, std::function<bool (UProperty*)> fnDone);
    template <>
    void IterateProperties(UFunction *func, std::function<bool (UProperty*)> fnDone);

    // Has been very useful so it gets to live here
    void dumpProperty(UProperty *p, void *container);


    // Works for numerics and some others.
    template <typename T>
    T *GetPropertyValue(UProperty *p, void *container) {
        return (T*)((uint64)container + p->Offset_Internal);
    }
    
    // UObject implementation
    template <>
    UObject *GetPropertyValue<UObject>(UProperty *p, void *container);

    // Searches object recursively for the path to get a property and its container.
    bool findPropertyByPath(UObject* object, void *container, std::string path, std::function<void (UProperty*,void *container)> fnFound);

    // Searches object recursively to retrieve the value of a child property.
    template <typename ValueType>
    ValueType *GetPropertyValueByPath(UObject* object, void *container, std::string path) {

        ValueType *value = nullptr;
        findPropertyByPath(object, container, path, [&](UProperty *p, void *container) {
            value = GetPropertyValue<ValueType>(p, container);
        });

        return value;
    }

    // GUObjectArray
    void IterateObjectArray(std::function<bool (UObject*)> fnDone);
    UObject *FindObjectByName(char *objectName, char *className);

    // UObject utils
    bool HasFlags(UObject *object, EClassCastFlags flags);
}



// TODO templatify 
template <class T>
void hexDumpValue(const unsigned char * p, unsigned int offset);
void hexDump16Bytes(const unsigned char * p, unsigned int offset);
void hexDump(const void * mem, unsigned int n);


// MOVE
//void dumpStructProperties(void *container, UProperty *p, int level, int maxLevel);
// Old stuff for debugging.
//void dumpObject(UObject *Object, int level);
void dumpField(UField *uf, int level);
//void dumpStruct(UStruct *us, int level);
//void dumpClass(UClass *ClassPrivate, int level);
//void dumpObject(UObject *Object, void *container, int level);
void dumpObjectArray(FUObjectArray* oa);
void dumpNameEntries();
//void dumpFunction(UFunction *fn, int level);
//void findObjectsByClassName(FUObjectArray* oa, char *name);
//UObject *findObjectByName(FUObjectArray *oa, char *objectName, char *className);

// TEMP
//UProperty *findPropertyByName(UStruct *us, char *name);
//UProperty* findPropertyByPath(UObject* object, void *container, std::string path, void **outContainer);


//char * getNameFull(UObject *Object);

//void iterateObjectArray(FUObjectArray *oa, std::function<bool (UObject*)> fnDone);
UProperty *iterateStruct(UStruct* us, std::function<bool (UProperty*)> fnDone);
UProperty *iterateFunc(UFunction* func, std::function<bool (UProperty*)> fnDone);
void iterateArray(FScriptArray *arr, UArrayProperty *ap, std::function<bool (uint8*)> fnDone);

// void iterateProperties(UObject *obj, std::function<bool (UProperty*)> fnDone);
// void iterateProperties(UStruct *strct, std::function<bool (UProperty*)> fnDone);
// void iterateProperties(UFunction *func, std::function<bool (UProperty*)> fnDone);
// void iterateProperties(UClass *cls, std::function<bool (UField*)> fnDone);
bool iteratePropertiesRecursive(UObject *obj, void *container, int level, std::function<bool (UProperty* p,void *data,int depth)> fnDone);
bool iterateFieldsRecursive(UObject *obj, void *container, int depth, std::function<bool (UField*,void *data, int depth)> fnDone);


// TODO Just make a bool IsClassType(UOBject *, flag);
// And IsParmType(..)

bool IsClass(UObject *object, EClassCastFlags flags);

// bool IsByteProperty(UProperty *p);
// bool IsFloatProperty(UProperty *p);
// bool IsIntProperty(UProperty *p);
// bool IsUIntProperty(UProperty *p);
// bool IsInt16Property(UProperty *p);
// bool IsUInt16Property(UProperty *p);
// bool IsInt64Property(UProperty *p);
// bool IsUInt64Property(UProperty *p);
// bool IsBoolProperty(UProperty *p);
// bool IsNameProperty(UProperty *p);
// bool IsStructProperty(UProperty *p);
// bool IsStrProperty(UProperty *p);
// bool IsTextProperty(UProperty *p);
// bool IsMulticastDelegateProperty(UProperty *p);
// bool IsObjectProperty(UProperty *p);
// bool IsEnumProperty(UProperty *p);
// bool IsReturnParm(UProperty *p);
// bool IsOutParm(UProperty *p);

uint8 *GetBytePropertyValue(void *container, UProperty *p);
// float *GetFloatPropertyValue(void *container, UProperty *p);
// int32 *GetIntPropertyValue(void *container, UProperty *p);
// uint64 *GetUInt64PropertyValue(void *container, UProperty *p);
// int64 *GetInt64PropertyValue(void *container, UProperty *p);
// int16 *GetInt16PropertyValue(void *container, UProperty *p);
// uint16 *GetUInt16PropertyValue(void *container, UProperty *p);
// FName *GetNamePropertyValue(void *container, UProperty *p);
// FString *GetStrPropertyValue(void *container, UProperty *p);
// FText *GetTextPropertyValue(void *container, UProperty *p);
//FScriptArray *GetArrayPropertyValue(void *container, UProperty *p);
//UObject* GetObjectPropertyValue(void *container, UProperty *p);
//void* GetStructPropertyValue(void *container, UProperty *p);


bool GetBoolPropertyValue(void *container, UProperty *p);
uint64 *GetEnumPropertyValue(void *container, UProperty *p);
void GetMulticastDelegatePropertyValue(void *container, UProperty *p);
