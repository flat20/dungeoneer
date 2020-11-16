#include "helpers.h"
#include "unrealspy.h"
#include "unreal_impl.h"
#include <wchar.h>

namespace spy {

    TCHAR buf[100];

    // TODO new(buf)
	TCHAR *GetName(UObject *obj) {
        if (obj == nullptr) {
            return nullptr;
        }

        auto ToString = GetFunction<tFName_ToString>(RefFName_ToString);
        FName Name = obj->GetFName();

        uint32 len = ToString(&Name,&buf[0], 100);
        return &buf[0];
	}

	TCHAR *GetName(FName Name) {
        auto ToString = GetFunction<tFName_ToString>(RefFName_ToString);
        uint32 len = ToString(&Name,&buf[0], 100);
        return &buf[0];
	}

	UObject *FindObjectByName(TCHAR *ObjectName, TCHAR *ClassName, TCHAR *OuterName) {

        for (spy::FRawObjectIterator It(false); It; ++It) {

            UObject *obj = *It;

            // if objectName is requested but doesn't match, continue
            if (ObjectName != nullptr && wcscmp(GetName(obj), ObjectName) != 0) {
                continue;
            }

            // if className is requested but doesn't match, continue
            if (ClassName != nullptr && wcscmp(GetName(obj->GetClass()), ClassName) != 0) {
                continue;
            }

            // if OuterName is requested but doesn't match, continue
            if (OuterName != nullptr && wcscmp(GetName(obj->GetOuter()), OuterName) != 0) {
                continue;
            }

            return obj;

        }

        return nullptr;
	}

}