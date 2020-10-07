
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ios>
#include <sstream>
#include <string.h>

#include <bitset>
#include "unreal.h"
#include "util.h"

// These function won't work without the global GNames.
// Could have created a class but then every function on the planet would
// require that class passed to them. And Unreal Engine makes GNames
// global for convenience anyway.
namespace util {

    TNameEntryArray* GNames;
    FUObjectArray* GUObjectArray;

    char *getName(FName name) {
        const FNameEntry *entry = GNames->GetByIndex(name.Index);
        if (entry == nullptr) {
            return nullptr;
        }

        return (char *)&entry->AnsiName[0];
    }
    char *getName(UObject *Object) {
        if (Object == nullptr) {
            return nullptr;
        }
        return getName(Object->NamePrivate);
    }

    void iterate(UObject *baseObject, std::function<bool (UProperty*)> fnDone) {
        if (IsClass(baseObject, CASTCLASS_UStruct)) {
            iterateProperties((UStruct *)baseObject, fnDone);
        } else if (IsClass(baseObject, CASTCLASS_UFunction)) {
            iterateProperties((UFunction *)baseObject, fnDone);
        //  } else if (IsClass(baseObject, CASTCLASS_UClass)) {
        //      iterateProperties((UClass *)baseObject, fnDone);
        } else { // UObject
            iterateProperties(baseObject, fnDone);
        }
    }

    bool findPropertyByPath(UObject* object, void *container, std::string path, std::function<void (UProperty*,void *container)> fnFound) {

        std::string name;
        int delimiter = path.find_first_of("/");
        if (delimiter != std::string::npos) {
            name = path.substr(0, delimiter);
            path = path.substr(delimiter+1, path.length());
        } else {
            name = path;
            path = "";
        }

        UProperty *foundProperty = nullptr;

        // Search all properties for 'name'
        iterate(object, [&](UProperty *p) {

            // Not the property we're looking for, continue
            if (strcmp(getName(p), name.c_str()) != 0) {
                return false;
            }

            // Found property, do we need to go deeper?
            if (path.length() > 0) {

                // Step inside property if needed
                if (IsClass(p, CASTCLASS_UStructProperty)) {
                    UStructProperty *sp = (UStructProperty*)p;
                    UScriptStruct* v = sp->Struct;
                    if (v != nullptr) {
                        void *nextContainer = (void*)((uint64)container + p->Offset_Internal);
                        return findPropertyByPath(v, nextContainer, path, fnFound);
                    }

                } else if (IsClass(p, CASTCLASS_UObjectProperty)) {
                    UObject *v = GetPropertyValue<UObject>(p, container);
                    if (v != nullptr) {
                        void *nextContainer = v;
                        return findPropertyByPath(v, nextContainer, path, fnFound);
                    }
                    
                }

                // Can't go deeper, give up looking
                return true;
            }


            // Found a match - Now return it and a usable place to find its value.
            foundProperty = p;
            fnFound(p, container);

            return true;
        });

        // This is where we should fill in a struct to return.
        if (foundProperty != nullptr) {
            return true;
        }

        return false;

    }

    void dumpProperty(UProperty *p, void *container) {

        printf("%s", getName(p));
        printf("(%s)", getName(p->ClassPrivate));

        printf("offset:%x", p->Offset_Internal);

        printf(",PropertyFlags:%llx", p->PropertyFlags);
        printf(",ArrayDim:%x,ElementSize:%x", p->ArrayDim, p->ElementSize);
        // The first encountered property is assumed to be the input value so initialize this with the user-specified value from InPropertyValue
        if ((p->PropertyFlags & CPF_Parm) == CPF_Parm) {//(CPF_Parm) && !Property->HasAnyPropertyFlags(CPF_ReturnParm) && bFirstProperty)
            printf(",Param");
        }
        if ((p->PropertyFlags & CPF_ReferenceParm) == CPF_ReferenceParm) {
            printf(",Reference");
        }
        if ((p->PropertyFlags & CPF_OutParm) == CPF_OutParm) {
            printf(",Out");
        }
        if ((p->PropertyFlags & CPF_ReturnParm) == CPF_ReturnParm) {
            printf(",Return");
        }
        if ((p->PropertyFlags & CPF_ReturnParm) == CPF_ReturnParm) {
            printf(",PlainOld");
        }

        if (IsClass(p, CASTCLASS_UByteProperty)) {
            printf("=%d", *GetPropertyValue<uint8>(p, container));
        }
        if (IsClass(p, CASTCLASS_UFloatProperty)) {
            printf("=%f", *GetPropertyValue<float>(p, container));
        }
        if (IsClass(p, CASTCLASS_UDoubleProperty)) {
            printf("=%f", *GetPropertyValue<double>(p, container));
        }

        if (IsClass(p, CASTCLASS_UIntProperty)) {
            printf("=%I32d", *GetPropertyValue<int32>(p, container));
        }
        if (IsClass(p, CASTCLASS_UUInt32Property)) {
            printf("=%I32d", *GetPropertyValue<uint32>(p, container));
        }
        if (IsClass(p, CASTCLASS_UInt16Property)) {
            printf("=%I16d", *GetPropertyValue<int16>(p, container));
        }
        if (IsClass(p, CASTCLASS_UUInt16Property)) {
            printf("=%U16d", *GetPropertyValue<uint16>(p, container));
        }

        if (IsClass(p, CASTCLASS_UBoolProperty)) {
            bool v = GetBoolPropertyValue(container, p);
            printf("=%s", v ? "true" : "false");
        }

        if (IsClass(p, CASTCLASS_UStrProperty)) {
            FString *v = GetPropertyValue<FString>(p, container);
            printf("=%d,%d", v->Data.ArrayNum, v->Data.ArrayMax);
            if ((void*)v->Data.Data != nullptr) {
                printf("=%ls", (wchar_t*)v->Data.Data);
            } else {
                printf("=nullptr");
            }
        }

        if (IsClass(p, CASTCLASS_UNameProperty)) {
            FName *v = GetPropertyValue<FName>(p, container);
            printf("=%s", getName(*v));
        }

        // // What about looking for CASTCLASS_UScriptStruct or _UStructProp
        if (IsClass(p, CASTCLASS_UStructProperty)) {
            void *structAddr = (void*)((uint64)container + p->Offset_Internal);
            UStructProperty *sp = (UStructProperty*)p;
            UScriptStruct* scriptStruct = sp->Struct;
            if (scriptStruct == nullptr) {
                printf("=structisnull\n");
            }
        }



        // if (IsTextProperty(p)) {
        //     FText *v = GetPropertyValue<FText>(p, container);
        //     if (v != nullptr) {
        //         FString *s = (FString*)v->TextData.Object->LocalizedString.Object;
        //         if (s != nullptr) {
        //             if (s->Data.Data != nullptr) {
        //                 printf("=%ls", (wchar_t*)s->Data.Data);
        //             } else {
        //                 printf("=nullptr");
        //             }
        //         } else {
        //             printf("=nullptr");
        //         }
        //     } else {
        //         printf("=nullptr");
        //     }
        // }

        if (strcmp(getName(p->ClassPrivate), "MulticastDelegateProperty") == 0) {
    //    if (IsMulticastDelegateProperty(p)) {
            //GetMulticastDelegatePropertyValue(container, p);
        }


        // if (IsEnumProperty(p)) {
        //     uint64 *v = GetEnumPropertyValue(container, p);
        //     printf("=%lld", *v);
        // }


        // if (IsObjectProperty(p) && level < maxLevel) {
        //     //printf(",flags:%llx", p->ClassPrivate->ClassCastFlags);
        //     UObject *v = GetObjectPropertyValue(container, p);
        //     printf("=%s", getName(v));
        //     // if (v != nullptr) {
        //     //     printf("\n");
        //     //     //dumpObject(v, v, level+1);
        //     // }
        // }

        // if (IsClass(p, CASTCLASS_UArrayProperty)) {
        //     FScriptArray *v = GetArrayPropertyValue(container, p);
        //     UArrayProperty *ap = (UArrayProperty*)p;
        //     UProperty *inner = ap->Inner;
        //     printf(",innerClass:%s,innerEleSize:%x,innerFlags:%llx,innerCastFlags:%x", getName(inner->ClassPrivate), inner->ElementSize, inner->PropertyFlags, inner->ObjectFlags);
        //     printf("=%d,%d,%llx", v->ArrayNum, v->ArrayMax, (uint64)v->Data);
        //     if(v->ArrayMax == 0 || v->Data == nullptr) {
        //         printf(",nodata");
        //         return;
        //     }
        //     int i=0;
        //     iterateArray(v, ap, [&](uint8* data) {
        //         printf("\n%*s", level*2, "");
        //         printf("Array Element %d\n", i);
        //         hexDump(data, inner->ElementSize);
        //         i++;
        //         return false;
        //     });
            
        // }
    }

    template <>
    UObject *GetPropertyValue<UObject>(UProperty *p, void *container) {

        if (!IsClass(p, CASTCLASS_UObjectPropertyBase)) {
            printf("Not an object?");
            return nullptr;
        }

        UObjectPropertyBase *baseProp = (UObjectPropertyBase*)p;
        UObject **ptr = (UObject**)((uintptr_t)container + p->Offset_Internal);
        if (*ptr == nullptr || (uintptr_t)*ptr == MAX_uint64) {
            return nullptr;
        }

        UObject *obj = *ptr;
        return obj;
    }


    // TODO Maybe return FUObjectItem here so the user can choose between UObject and FUObjectItem
    void IterateObjectArray(std::function<bool (UObject*)> fnDone) {
        TUObjectArray objObjects = GUObjectArray->ObjObjects;
        int index = 0;
        for (index = 0; index < objObjects.NumElements; index++) {
            int chunk = index / TUObjectArray::NumElementsPerChunk;
            int chunkOffset = index % TUObjectArray::NumElementsPerChunk;
            FUObjectItem item = objObjects.Objects[chunk][chunkOffset];
            if (fnDone(item.Object)) {
                return;
            }
        }
    }

    // Finds one UObject with exactly matching name and class. nullptr = skip
    // Use with care since uobject names don't have to be unique and this will return the first one.
    // TODO Perhaps FName is a better search parameter?
    UObject *FindObjectByName(char *objectName, char *className) {
        UObject *found = nullptr;
        IterateObjectArray([&](UObject *object) {

            // if objectName is requested but doesn't match, continue
            if (objectName != nullptr && strcmp(getName(object), objectName) != 0) {
                return false;
            }

            // if className is requested but doesn't match, continue
            if (className != nullptr && strcmp(getName(object->ClassPrivate), className) != 0) {
                return false;
            }

            // Must be a match
            found = object;
            return true;
        });
        return found;
    }

}

using namespace util;


// char * getNameFull(UObject *Object) {
//     char name[2048];

//     int i = 2046; // Leaving one char for a null
//     do {
//         const FNameEntry *entry = GNames->GetByIndex(Object->NamePrivate.Index);
//         if (entry != nullptr) {
//             printf("\ni: %d %s len %d\n", i, entry->AnsiName, (int)strlen(entry->AnsiName));
//             i = i - (strlen(entry->AnsiName) + 1); // "/" + name
//             printf(" then i: %d\n", i);
//             name[i] = '/';
//             strncpy(&name[i+1], entry->AnsiName, strlen(entry->AnsiName));
// //            sprintf(&name[i], "/%s", entry->AnsiName);
//             printf(&name[i]);
//         }
//         //printf("%llx %llx\n", (DWORD64)Object, (DWORD64)Object->ClassPrivate);
//         Object = Object->ClassPrivate;
//     } while (Object != nullptr && Object->ClassPrivate != nullptr && Object->ClassPrivate != Object);
//     name[2047] = 0;
//     return &name[i];
// }

// char * getName(UObject *Object) {
//     if (Object == nullptr) {
//         return nullptr;
//     }
//     const FNameEntry *entry = GNames->GetByIndex(Object->NamePrivate.Index);
//     if (entry == nullptr) {
//         return nullptr;
//     }

//     return (char *)&entry->AnsiName[0];
// }


// UObject * GetObjectByNameIndex(FUObjectArray* oa, NAME_INDEX NameIndex) {

//     int n = oa->ObjObjects.NumElements;
//     for (int Index=0; Index<n; Index++) {
//         int Chunk = Chunk = Index / TUObjectArray::NumElementsPerChunk;
//         int ChunkOffset = Index % TUObjectArray::NumElementsPerChunk;
//         FUObjectItem item = oa->ObjObjects.Objects[Chunk][ChunkOffset];
//         if (item.Object == nullptr) {
//             continue;
//         }

//         if (item.Object->NamePrivate.Index == NameIndex) {
//             return item.Object;
//         }

//     }

//     return nullptr;
// }


// UObject * GetObjectByName(FUObjectArray* oa, char *name) {

//     int n = oa->ObjObjects.NumElements;
//     for (int Index=0; Index<n; Index++) {
//         int Chunk = Chunk = Index / TUObjectArray::NumElementsPerChunk;
//         int ChunkOffset = Index % TUObjectArray::NumElementsPerChunk;
//         FUObjectItem item = oa->ObjObjects.Objects[Chunk][ChunkOffset];

//         if (item.Object == nullptr) {
//             continue;
//         }

//         char *objName = getName(item.Object);
//         if (strcmp(objName, name) == 0) {
//             return item.Object;
//         }

//     }

//     return nullptr;
// }

bool IsClass(UObject *object, EClassCastFlags flag) {
    return (object->ClassPrivate->ClassCastFlags & flag) == flag;
}

// bool IsByteProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UByteProperty) == CASTCLASS_UByteProperty;
// }

// bool IsFloatProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UFloatProperty) == CASTCLASS_UFloatProperty;
// }
// bool IsIntProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UIntProperty) == CASTCLASS_UIntProperty;
// }
// bool IsUIntProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UIntProperty) == CASTCLASS_UIntProperty;
// }
// bool IsInt16Property(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UInt16Property) == CASTCLASS_UInt16Property;
// }
// bool IsUInt16Property(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UUInt16Property) == CASTCLASS_UUInt16Property;
// }
// bool IsInt64Property(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UInt64Property) == CASTCLASS_UInt64Property;
// }
// bool IsUInt64Property(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UUInt64Property) == CASTCLASS_UUInt64Property;
// }
// bool IsBoolProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UBoolProperty) == CASTCLASS_UBoolProperty;
// }

// bool IsNameProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UNameProperty) == CASTCLASS_UNameProperty;
// }


// bool IsStructProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UStructProperty) == CASTCLASS_UStructProperty;
// }


// bool IsStrProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UStrProperty) == CASTCLASS_UStrProperty;
// }

// bool IsTextProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UTextProperty) == CASTCLASS_UTextProperty;
// }
// bool IsMulticastDelegateProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UMulticastDelegateProperty) == CASTCLASS_UMulticastDelegateProperty;
// }
// bool IsObjectProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UObjectProperty) == CASTCLASS_UObjectProperty;
// }
// bool IsEnumProperty(UProperty *p) {
//     return (p->ClassPrivate->ClassCastFlags & CASTCLASS_UEnumProperty) == CASTCLASS_UEnumProperty;
// }
// bool IsReturnParm(UProperty *p) {
//     return (p->PropertyFlags & CPF_ReturnParm) == CPF_ReturnParm;
// }
// bool IsOutParm(UProperty *p) {
//     return (p->PropertyFlags & CPF_OutParm) == CPF_OutParm;
// }

uint8 *GetBytePropertyValue(void *container, UProperty *p) {
    return (uint8*)((uint64)container + p->Offset_Internal);
}
// float *GetFloatPropertyValue(void *container, UProperty *p) {
//     return (float*)((uint64)container + p->Offset_Internal);
// }

// int32 *GetIntPropertyValue(void *container, UProperty *p) {
//     return (int32*)((uint64)container + p->Offset_Internal);
// }


// uint64 *GetUInt64PropertyValue(void *container, UProperty *p) {
//     return (uint64*)((uint64)container + p->Offset_Internal);
// }

// int64 *GetInt64PropertyValue(void *container, UProperty *p) {
//     return (int64*)((uint64)container + p->Offset_Internal);
// }

// int16 *GetInt16PropertyValue(void *container, UProperty *p) {
//     return (int16*)((uint64)container + p->Offset_Internal);
// }
// uint16 *GetUInt16PropertyValue(void *container, UProperty *p) {
//     return (uint16*)((uint64)container + p->Offset_Internal);
// }



bool GetBoolPropertyValue(void *container, UProperty *p) {
    UBoolProperty *bp = (UBoolProperty *)p;
    uint8* ByteValue = (uint8*)container + bp->ByteOffset;
	return !!(*ByteValue & bp->FieldMask);
}

// FName *GetNamePropertyValue(void *container, UProperty *p) {
//     return (FName *)((uint64)container + p->Offset_Internal);
// }

// FString *GetStrPropertyValue(void *container, UProperty *p) {
//     return (FString *)((uint64)container + p->Offset_Internal);
// }

// FText *GetTextPropertyValue(void *container, UProperty *p) {
//     return (FText *)((uint64)container + p->Offset_Internal);
// }

// TODO Fix this. It never works.
uint64 *GetEnumPropertyValue(void *container, UProperty *p) {
    return nullptr;

    UEnumProperty *ep = (UEnumProperty*)p;
    if (ep->Enum != nullptr) {
        printf("enum represented by this prop names num %d max %d cppform: %d\n", ep->Enum->Names.ArrayNum, ep->Enum->Names.ArrayMax, ep->Enum->CppForm);
    }
    if (ep->UnderlyingProp != nullptr) {
        printf("underlying: %llx offs %x\n", (uint64)ep->UnderlyingProp, ep->UnderlyingProp->Offset_Internal);
        printf("value underlying? %d\n", *(uint8*)((uint64)container + ep->UnderlyingProp->Offset_Internal));
    }
    printf("value? %d\n", *(uint8*)((uint64)container + p->Offset_Internal));
    switch(ep->ElementSize) {
        case 1:
            return (uint64*)(uint8*)((uint64)container + p->Offset_Internal);
        case 2:
            return (uint64*)(uint16*)((uint64)container + p->Offset_Internal);
        case 4:
            return (uint64*)((uint64)container + p->Offset_Internal);
        default:
            return nullptr;
    }

}

// FScriptArray *GetArrayPropertyValue(void *container, UProperty *p) {
//     return (FScriptArray *)((uint64)container + p->Offset_Internal);
// }




// Return a pointer to the data container for the given UStructProperty
// void* GetStructPropertyValue(void *container, UProperty *p) {
//     return (void*)((uint64)container + p->Offset_Internal);
// }


// TODO templatify 
template <class T>
void hexDumpValue(const unsigned char * p, unsigned int offset) {
    const int width = sizeof(T)*2; // 16, times two for hex
    const T * valuePtr = reinterpret_cast< const T *>( p+offset );
    for (int i=0; i<16; i+=sizeof(T)) {
        //std::cout << "  =" << std::setw(width) << std::setfill( ' ' ) << *valuePtr;
        std::cout << "  =" << *valuePtr;
        valuePtr++;
    }
}

void hexDump16Bytes(const unsigned char * p, unsigned int offset) {
    
    // address and offset
    std::cout << std::setw(12) << std::setfill( '0' ) << std::hex << (uint64_t)p+offset;
    std::cout << "  ";
    std::cout << std::setw(4) << offset;
    std::cout << "  ";

    unsigned int n = 16;
    for ( unsigned int i = 0; i < n; i++ ) {
        if (i % 8 == 0) {   // space
            std::cout << "  ";
        }
        
        std::cout << std::setw(2) << std::setfill( '0' ) << std::hex << int(p[offset+i]) << " ";
    }

    hexDumpValue<uint64_t>(p, offset);
    //hexDumpValue<float>(p, offset);

    std::cout << std::endl;
}

void hexDump(const void * mem, unsigned int n) {

    const unsigned char * p = reinterpret_cast< const unsigned char *>( mem );
    for ( unsigned int i = 0; i < n; i+=16 ) {
        hexDump16Bytes(p, i);
    }

}



void dumpField(UField *uf, int level) {
    printf("%*s UField %llx\n", level, " ", (uint64)uf);
    printf("%*s UField.Next %llx\n", level, " ", (uint64)uf->Next);
    //dumpObject(uf, level+1);
    if (uf->Next != nullptr) {
        dumpField(uf->Next, level+1);
    }
    
}

// void dumpStruct(UStruct *us, int level) {
//     printf("%*s UStruct %llx\n", level, " ", (uint64)us);
//     //printf("%*s UStruct.StructBaseChainArray %llx\n", level, " ", us->StructBaseChainArray);
//     //printf("%*s UStruct.NumStructBasesInChainMinusOne %d\n", level, " ", us->NumStructBasesInChainMinusOne);

//     printf("%*s UStruct.SuperStruct %llx\n", level, " ", (uint64)us->SuperStruct);
//     printf("%*s UStruct.Children %llx\n", level, " ", (uint64)us->Children);
//     printf("%*s UStruct.PropertiesSize %d\n", level, " ", us->PropertiesSize);
//     printf("%*s UStruct.MinAlignment %d\n", level, " ", us->MinAlignment);
//     printf("%*s UStruct.Script.Num %llx\n", level, " ", (uint64)us->Script.ArrayNum);
//     printf("%*s UStruct.PropertyLink %llx\n", level, " ", (uint64)us->PropertyLink);
//     printf("%*s UStruct.RefLink %llx\n", level, " ", (uint64)us->RefLink);
//     printf("%*s UStruct.DestructorLink %llx\n", level, " ", (uint64)us->DestructorLink);
//     printf("%*s UStruct.PostConstructLink %llx\n", level, " ", (uint64)us->PostConstructLink);
//     printf("%*s UStruct.ScriptObjectReferences.Num %llx\n", level, " ", (uint64)us->ScriptObjectReferences.Data);

//     //dumpField(us, level);
// }

// void dumpClass(UClass *ClassPrivate, int level) {
//     printf("%*s UClass %llx\n", level, " ", (uint64)ClassPrivate);
//     printf("%*s UClass.Name %s\n", level, " ", getName(ClassPrivate));

//     // Also has all the dumpObject stuff
//     printf("%*s UClass.PropertiesSize %d\n", level, " ", ClassPrivate->PropertiesSize);
//     printf("%*s UClass.MinAlignment %d\n", level, " ", ClassPrivate->MinAlignment);
//     printf("%*s UClass.bCooked %s\n", level, " ", ClassPrivate->bCooked ? "true" : "false");
    
//     printf("%*s UClass.ClassFlags %x %s\n", level, " ", ClassPrivate->ClassFlags, std::bitset<32>(ClassPrivate->ClassFlags).to_string().c_str());
// //    std::cout << std::bitset<32>(ClassPrivate->ClassFlags).to_string();
//     printf("%*s UClass.ClassCastFlags %llx %s\n", level, " ", ClassPrivate->ClassCastFlags, std::bitset<64>(ClassPrivate->ClassCastFlags).to_string().c_str());
//     //printf("    ClassPrivate %llx\n", (DWORD64)ClassPrivate);
//     // Dump uObject parts here as well?
//     //dumpStruct(ClassPrivate, level);

//     //dumpObject(ClassPrivate, level);
//     // dumpStruct()
//     // dumpUField
       
        
//         // printf("%*s UClass.Children %llx\n", level, " ", (DWORD64)ClassPrivate->Children);
 
//         // if (ClassPrivate->Children != nullptr) {
//         //     UField* child = ClassPrivate->Children;
//         //     while (child != nullptr) {
//         //         printf("%*s  %llx\n", level, " ", (DWORD64)child);
//         //         printf("%*s  internal index %d\n", level, " ", child->InternalIndex);
//         //         printf("%*s  flags %x\n", level, " ", child->ObjectFlags);
//         //         const FNameEntry *ne = GNames->GetByIndex(child->NamePrivate.Index);
//         //         if (ne != nullptr) {
//         //             printf("        %s\n", ne->AnsiName);
//         //         } else {
//         //             printf("        [noname]\n");
//         //         }
//         //         printf("next child %llx\n", (DWORD64)child->Next);
//         //         child = child->Next;
//         //     }
//         // }
    
// }

// TODO indentation
// what's the linked list for in fnames?
void dumpObjectArray(FUObjectArray* oa) {
    
    std::ofstream myfile("objects.txt", std::ofstream::out);
    int n = oa->ObjObjects.NumElements;
    for (int Index=0; Index<n; Index++) {
        int Chunk = Chunk = Index / TUObjectArray::NumElementsPerChunk;
        int ChunkOffset = Index % TUObjectArray::NumElementsPerChunk;
        FUObjectItem item = oa->ObjObjects.Objects[Chunk][ChunkOffset];
        //printf("%d Chunk %d Ofs %d %llx\n", Index, Chunk, ChunkOffset, (uint64)item.Object);
        
        //printf("%s (%s)\n", getName(item.Object), getName(item.Object->ClassPrivate));
        myfile << getName(item.Object) << " (" << getName(item.Object->ClassPrivate) << ")" << std::endl;
        //printFullObjectName(item.Object);
        for (UProperty* p = item.Object->ClassPrivate->PropertyLink; p; p = p->PropertyLinkNext)
        {
            //printf("  %s (%s)\n", getName(p), getName(p->ClassPrivate));
            myfile << "  " << getName(p) << " (" << getName(p->ClassPrivate) << ")" << std::endl;
        }

    }
    myfile.close();

}


void dumpNameEntries() {
    std::ofstream myfile("nameentries.txt", std::ofstream::out);
    //myfile.open ("c:\\nameentries.txt");

    for (int32 i = 0; i < GNames->Num(); i++) { //GNames->Num(); i++)
        const FNameEntry *entry = GNames->GetByIndex(i);
        if (entry == nullptr)
            continue;
        myfile << i << " NameIndex " << entry->Index << " " << entry->AnsiName << std::endl;
        std::cout << i << " NameIndex " << entry->Index << " " << entry->AnsiName << std::endl;
    }
    myfile.close();
}

// void dumpFunction(UFunction *fn, int level) {
   
//     printf("%*s Function %llx\n", level, " ", (uint64)fn);

//     printf("%*s Function.FunctionFlags %x %s\n", level, " ", fn->FunctionFlags, std::bitset<32>(fn->FunctionFlags).to_string().c_str());
//     printf("%*s Function.NumParms %d\n", level, " ", fn->NumParms);
//     printf("%*s Function.ParmsSize %d\n", level, " ", fn->ParmsSize);
//     printf("%*s Function.ReturnValueOffset %d\n", level, " ", fn->ReturnValueOffset);
//     //printf("%*s Function.RPCId %d\n", level, " ", fn->RPCId);
//     //printf("%*s Function.RPCResponseId %d\n", level, " ", fn->RPCResponseId);
//     //printf("%*s Function.FirstPropertyToInit %llx\n", level, " ", (DWORD64)fn->FirstPropertyToInit);
//     //printf("%*s Function.EventGraphFunction %llx\n", level, " ", (DWORD64)fn->EventGraphFunction);
//     //printf("%*s Function.EventGraphCallOffset %d\n", level, " ", fn->EventGraphCallOffset);
//     printf("%*s Function.Func %llx\n", level, " ", (uint64)fn->Func);
//     printf("%*s Function.HasDefaults %s\n", level, "", (fn->FunctionFlags & FUNC_HasDefaults) == FUNC_HasDefaults ? "true" : "false");
//     printf("%*s Function.Native %s\n", level, "", (fn->FunctionFlags & FUNC_Native) == FUNC_Native ? "true" : "false");
//     printf("%*s Function.Setter Thing %s\n", level, "", fn->ReturnValueOffset != MAX_uint16 || fn->NumParms > 1 ? "true" : "false");

//     // MovieSceneCommonHelper
//     //if (Setter->ReturnValueOffset != MAX_uint16 || Setter->NumParms > 1)
    
// }


// void findObjectsByClassName(FUObjectArray* oa, char *name) {
    
//     iterateObjectArray(oa, [&](UObject *object) {
//         UObject *classPrivate = object->ClassPrivate;
//         if (classPrivate == nullptr) {
//             return false;
//         }

//         char *className = getName(classPrivate);
//         if (className == nullptr || strstr(className, name) == nullptr) {
//             return false;
//         }

//         printf("%s FName %d.%d InternalIndex: %d  Class: %s FName %d.%d InternalIndex: %d\n", 
//             getName(object), object->NamePrivate.Index, object->NamePrivate.Number, object->InternalIndex,
//             className, classPrivate->NamePrivate.Index, classPrivate->NamePrivate.Number, classPrivate->InternalIndex
//         );
//         return false;
//     });

// }


// Iterate a UStruct with a lambda callback
// Also returns the UProperty* if fnDone is successful.
UProperty *iterateStruct(UStruct* us, std::function<bool (UProperty*)> fnDone) {
    for (UProperty* p = us->PropertyLink; p; p = p->PropertyLinkNext) {
        if (fnDone(p) == true) {
            return p;
        }
    }
    return nullptr;
}

// Iterate a function parameters, which actually is a struct with some additional checks.
UProperty *iterateFunc(UFunction* func, std::function<bool (UProperty*)> fnDone) {
    return iterateStruct(func, [&](UProperty *p) {
        // Initialize the parameter pack with any param properties that reside in the container
        int size = p->ArrayDim * p->ElementSize;
        if (p->Offset_Internal + size <= func->ParmsSize) //Offset_Internal + GetSize() <= ContainerSize;
        {
            return fnDone(p);
        }
        return false;
    });
}

// TODO Maybe pass in ElementSize instead of the UArrayProperty
// TODO Could also template the uint8 if that helps with casting.
void iterateArray(FScriptArray *arr, UArrayProperty *ap, std::function<bool (uint8*)> fnDone) {
    UProperty *inner = ap->Inner;
    if(arr->ArrayMax == 0 || arr->Data == nullptr) {
        return;
    }
    uint8 *ptr = (uint8*)arr->Data;
    for (int i=0; i<arr->ArrayNum; i++) {
        if (fnDone(ptr) == true) {
            return;
        }
        ptr += inner->ElementSize;
    }
}

// Can't we have a iterateObj with overloading based on the class passed in?
void iterateProperties(UObject *obj, std::function<bool (UProperty*)> fnDone) {
    for (UProperty *p = obj->ClassPrivate->PropertyLink; p != nullptr; p = p->PropertyLinkNext) {
        if (fnDone(p)) {
            return;
        }
    }
    return;
}

void iterateProperties(UFunction *func, std::function<bool (UProperty*)> fnDone) {
    iterateProperties((UStruct*)func, [&](UProperty *p){
        // Initialize the parameter pack with any param properties that reside in the container
        int size = p->ArrayDim * p->ElementSize;
        if (p->Offset_Internal + size <= func->ParmsSize) { //Offset_Internal + GetSize() <= ContainerSize;
            return fnDone(p);
        }
        return false;
    });
}

void iterateProperties(UStruct *strct, std::function<bool (UProperty*)> fnDone) {
    for (UProperty* p = strct->PropertyLink; p; p = p->PropertyLinkNext) {
        if (fnDone(p)) {
            return;
        }
    }
    return;
}




// Iterate properties on UObject, UFunction, UClass, UArray etc.
// Could be handled with virtual functions on each of these classes, but can't add them since
// returning true = done/stop iterating.
bool iteratePropertiesRecursive(UObject *obj, void *container, int depth, std::function<bool (UProperty*,void *data, int depth)> fnDone) {
    if (obj == nullptr) {
        return false;
    }
    // Check if classPrivate is null?

    // Lambda to resolve this object's properties recursively.
    auto propsRecursive = [&](UProperty *p) {
        if (fnDone(p, container, depth)) {
            return true;
        };

        // Step inside property if needed
        if (IsClass(p, CASTCLASS_UStructProperty)) {
            //void *structAddr = (void*)((uint64)container + p->Offset_Internal);
            UStructProperty *sp = (UStructProperty*)p;
            UScriptStruct* v = sp->Struct;
            if (v != nullptr) {
                void *nextContainer = (void*)((uint64)container + p->Offset_Internal);
                return iteratePropertiesRecursive((UStruct *)v, nextContainer, depth+1, fnDone);
            }

        } else if (IsClass(p, CASTCLASS_UObjectProperty)) {
            printf("%*s obj property obj flags %x prop flags: %llx classflags: %x classcastflags: %llx\n", depth, "", p->ObjectFlags, p->PropertyFlags, p->ClassPrivate->ClassFlags, p->ClassPrivate->ClassCastFlags);
            //UObject *v = GetObjectPropertyValue(container, p);
            UObject *v = GetPropertyValue<UObject>(p, container);
            if (v != nullptr) {
                void *nextContainer = v;
                return iteratePropertiesRecursive((UObject *)v, nextContainer, depth+1, fnDone);
            }
            
        }

        return false;
    };

    // Cast obj to its correct class so iterateProperties() type overloading triggers.
    if (IsClass(obj, CASTCLASS_UFunction)) {
        iterateProperties((UFunction*)obj, propsRecursive);
        return false;
    }

    if (IsClass(obj, CASTCLASS_UStruct)) {
        iterateProperties((UStruct*)obj, propsRecursive);
        return false;
    }
    
    // Is it a UObject?? But everything is a UObject..
    iterateProperties((UObject*)obj, propsRecursive);
    return false;
    

}

// UProperty *findPropertyByName(UStruct *us, char *name) {

//     return iterateStruct(us, [&](UProperty *p) {

//         if (strcmp(getName(p), name) != 0) {
//             return false; // next
//         }
//         return true;
        
//     });

// }



// TODO


// template <typename T>
// T getPropertyValueByPath(UObject* object, void *container, std::string path) {
    
// }