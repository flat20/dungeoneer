
cl /nologo /EHsc ^
     /I dungeoneer/ /I unrealspy/ ^
     /FI C:\Users\andreas\code\dungeoneer\diet-ue\defines.h ^
     /I diet-ue/ ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Public" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Private" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\CoreUObject\Public" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Engine\Classes" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Engine\Public" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Public" ^
     simple-mod/*.cpp ^
     -link ^
      -DLL /subsystem:console /DEBUG -OUT:simple-mod.dll
