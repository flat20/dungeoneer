#include "helpers.h"
#include "unrealspy.h"
#include "unreal_impl.h"


namespace spy {

    // The reason we can't get a null terminated string is because
    // they're not stored with nulls in memory from 4.24+
    // we have to make a copy to a buffer... which means errors
    // if we want to stick with a simple call like GetName()

    ANSICHAR *GetName(UObject *obj) {
        if (obj == nullptr) {
            return nullptr;
        }

        FName Name = obj->GetFName();
        return GetName(Name);
    }

    // FNAME_TYPE *GetName(UObject *Object) {
    //     return GetName<FNAME_TYPE>(Object);
    // }


	ANSICHAR *GetName(FName Name) {
        static ANSICHAR buffer[NAME_SIZE];
        static auto GetEntry = GetFunction<tFName_GetEntry>(RefFName_GetEntry);

        FNameEntry *Entry = GetEntry(Name.GetDisplayIndex());
        Entry->GetAnsiName(buffer);
        return &buffer[0];
	}


    // Match Object name with the supplied names.
    UObject* FindObjectByName(ANSICHAR *ObjectName, ANSICHAR *ClassName, ANSICHAR *OuterName) {

        for (spy::FRawObjectIterator It(false); It; ++It) {

            UObject *Object = *It;

            // if objectName is requested but doesn't match, continue
            if (ObjectName != nullptr && FPlatformString::Strcmp(GetName(Object), ObjectName) != 0) {
                continue;
            }

            // if className is requested but doesn't match, continue
            if (ClassName != nullptr && FPlatformString::Strcmp(GetName(Object->GetClass()), ClassName) != 0) {
                continue;
            }

            // if OuterName is requested but doesn't match, continue
            if (OuterName != nullptr && FPlatformString::Strcmp(GetName(Object->GetOuter()), OuterName) != 0) {
                continue;
            }

            // all three matched
            return Object;
        }

        return nullptr;
    }

	// UObject *FindObjectByName(ANSICHAR *ObjectName, ANSICHAR *ClassName, ANSICHAR *OuterName) {
    //     return FindObjectByName<ANSICHAR>(ObjectName, ClassName, OuterName);
	// }

	// UObject *FindObjectByName(WIDECHAR *ObjectName, WIDECHAR *ClassName, WIDECHAR *OuterName) {
    //     return FindObjectByName<WIDECHAR>(ObjectName, ClassName, OuterName);
	// }

}