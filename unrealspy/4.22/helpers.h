#pragma once

#include "unrealspy.h"
#include "../defines.h"

namespace spy {
	
	template<typename T>
	T *GetName(UObject *obj);

    FNAME_TYPE *GetName(UObject *Object);

	TCHAR *GetName(FName Name);

	UObject *FindObjectByName(WIDECHAR *ObjectName, WIDECHAR *ClassName, WIDECHAR *OuterName);
	UObject *FindObjectByName(ANSICHAR *ObjectName, ANSICHAR *ClassName, ANSICHAR *OuterName);
}
