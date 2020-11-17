#include "helpers.h"
#include "unrealspy.h"
#include "unreal_impl.h"

namespace spy {

	// bool GetName(UObject *obj, ANSICHAR (&OutName)[1024]) {
	// 	FName name = obj->GetFName();
	// 	TNameEntryArray& Names = *GNames;

	// 	// Code from the ue source.
	// 	const NAME_INDEX Index = name.GetDisplayIndex();
	// 	const FNameEntry* const NameEntry = Names[Index];

	// 	// GetComparisonIndex() seems to be the same thing as display index?

	// 	NameEntry->GetAnsiName(OutName);
    //     return true;
	// }

//     // ANSICHAR, WIDECHAR, TCHAR?
//     template<typename T>
// 	T *GetName(UObject *obj) {
//         if (obj == nullptr) {
//             return nullptr;
//         }

//         // Give us direct access to the name char*
//         class QuickName : public ::FNameEntry {
//         public:
//             FORCEINLINE T *GetPtr()
//             {
//                 // Both point to the same address anyway
// //                if (IsWide()) {
// //                	return (TCHAR*)&WideName[0];
// //                } else {
//                     return (T*)&AnsiName[0];
//  //               } 
//             }
//         };

// 		FName name = obj->GetFName();
// 	}

    ANSICHAR *GetName(UObject *Object) {
        if (Object == nullptr) {
            return nullptr;
        }
        return GetName(Object->GetFName());
    }

    ANSICHAR *GetName(FName Name) {

        class QuickName : public ::FNameEntry {
        public:
            FORCEINLINE ANSICHAR *GetPtr()
            {
                // Both point to the same address anyway
//                if (IsWide()) {
//                	return (TCHAR*)&WideName[0];
//                } else {
                    return (ANSICHAR*)&AnsiName[0];
 //               } 
            }
        };

        TNameEntryArray& Names = *GNames;

		// Code from the ue source.
		const NAME_INDEX Index = Name.GetDisplayIndex();

        auto NameEntry = (QuickName*)Names[Index];
        return NameEntry->GetPtr();
    }

    // Match Object name with the supplied names.
    // template<typename T>
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