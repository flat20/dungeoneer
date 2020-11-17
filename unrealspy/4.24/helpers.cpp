#include "helpers.h"
#include "unrealspy.h"
#include "unreal_impl.h"

namespace spy {

    TCHAR buf[100];

    // TODO new(buf)
    // TODO Use FName::GetDisplayNameEntry {
    //    return &GetNamePool().Resolve(GetDisplayIndex());    
    //}
    // Or find .Resolve()
    // This one exists:
    // const struct FNameEntry *__fastcall FName::GetEntry(struct FNameEntryId)
    // How can we later loop all FNames?


    template <typename T>
	T *GetName(UObject *obj) {
        if (obj == nullptr) {
            return nullptr;
        }

        auto ToString = GetFunction<tFName_ToString>(RefFName_ToString);
        FName Name = obj->GetFName();

        uint32 len = ToString(&Name,&buf[0], 100);
        return (T*)&buf[0];
	}

    // // Might work?
    // template <typename T>
    // T *GetName(UObject *obj) {
    //     if (obj == nullptr) {
    //         return nullptr;
    //     }

    //     // No way to access AnsiName in 4.24
    //     class QuickName {//}: public ::FNameEntry {
    //     public:
    //     #if WITH_CASE_PRESERVING_NAME
    //         FNameEntryId ComparisonId;
    //     #endif
    //         FNameEntryHeader Header;
    //         union
    //         {
    //             ANSICHAR	AnsiName[NAME_SIZE];
    //             WIDECHAR	WideName[NAME_SIZE];
    //         };
    //         // FORCEINLINE T *GetPtr()
    //         // {
    //         //     return (T*)&AnsiName[0];
    //         // }
    //     };

    //     FName Name = obj->GetFName();

    //     static auto GetEntry = GetFunction<tFName_GetEntry>(RefFName_GetEntry);
    //     QuickName *Entry = (QuickName*)GetEntry(Name.GetDisplayIndex());
    //     return (T*)&Entry->AnsiName[0];
    // }

    FNAME_TYPE *GetName(UObject *Object) {
        return GetName<FNAME_TYPE>(Object);
    }


	TCHAR *GetName(FName Name) {
        auto ToString = GetFunction<tFName_ToString>(RefFName_ToString);
        uint32 len = ToString(&Name,&buf[0], 100);
        return &buf[0];
	}


    // Match Object name with the supplied names.
    template<typename T>
    UObject* FindObjectByName(T *ObjectName, T *ClassName, T *OuterName) {

        for (spy::FRawObjectIterator It(false); It; ++It) {

            UObject *Object = *It;

            // if objectName is requested but doesn't match, continue
            if (ObjectName != nullptr && FPlatformString::Strcmp(GetName<T>(Object), ObjectName) != 0) {
                continue;
            }

            // if className is requested but doesn't match, continue
            if (ClassName != nullptr && FPlatformString::Strcmp(GetName<T>(Object->GetClass()), ClassName) != 0) {
                continue;
            }

            // if OuterName is requested but doesn't match, continue
            if (OuterName != nullptr && FPlatformString::Strcmp(GetName<T>(Object->GetOuter()), OuterName) != 0) {
                continue;
            }

            // all three matched
            return Object;
        }

        return nullptr;
    }

	UObject *FindObjectByName(ANSICHAR *ObjectName, ANSICHAR *ClassName, ANSICHAR *OuterName) {
        return FindObjectByName<ANSICHAR>(ObjectName, ClassName, OuterName);
	}

	UObject *FindObjectByName(WIDECHAR *ObjectName, WIDECHAR *ClassName, WIDECHAR *OuterName) {
        return FindObjectByName<WIDECHAR>(ObjectName, ClassName, OuterName);
	}

}