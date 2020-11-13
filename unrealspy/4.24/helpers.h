#pragma once

#include "unrealspy.h"

namespace spy {
	//bool GetName(UObject *obj, ANSICHAR (&OutName)[1024]);
	// SPYAPI ANSICHAR *GetName(UObject *obj);
	TCHAR *GetName(UObject *obj);
	UObject *FindObjectByName(TCHAR *ObjectName, TCHAR *ClassName, TCHAR *OuterName);
}
