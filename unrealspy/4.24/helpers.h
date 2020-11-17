#pragma once

#include "unrealspy.h"

namespace spy {

	ANSICHAR *GetName(UObject *obj);

    // FNAME_TYPE *GetName(UObject *Object);

	ANSICHAR *GetName(FName Name);

	// UObject *FindObjectByName(WIDECHAR *ObjectName, WIDECHAR *ClassName, WIDECHAR *OuterName);
	UObject *FindObjectByName(ANSICHAR *ObjectName, ANSICHAR *ClassName, ANSICHAR *OuterName);
}
