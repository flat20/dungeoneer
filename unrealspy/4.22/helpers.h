#pragma once

#include "unrealspy.h"

namespace spy {
	
	// template<typename T>
	// T *GetName(UObject *obj);

    ANSICHAR *GetName(UObject *Object);

	ANSICHAR *GetName(FName Name);

	// UObject *FindObjectByName(WIDECHAR *ObjectName, WIDECHAR *ClassName, WIDECHAR *OuterName);
	UObject *FindObjectByName(ANSICHAR *ObjectName, ANSICHAR *ClassName, ANSICHAR *OuterName);
}
