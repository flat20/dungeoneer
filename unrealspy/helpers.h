#pragma once

#include <diet-ue.h>

namespace spy {
	bool GetName(UObject *obj, ANSICHAR (&OutName)[1024]);
	ANSICHAR *GetName(UObject *obj);
	UObject *FindObjectByName(char *ObjectName, char *ClassName);

}
