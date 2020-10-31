
cl /nologo /EHsc ^
     /I minhook-master/include/ /I unrealspy/ ^
     /I imgui-1.78/  ^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared"  ^
     /FI C:\Users\andreas\code\dungeoneer\diet-ue\defines.h ^
     /I diet-ue/ ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Public" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Private" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\CoreUObject\Public" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Engine\Classes" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Engine\Public" ^
     /I "D:\UnrealEngine-4.22\Engine\Source\Runtime\Core\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Engine\Classes" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\EngineSettings\Classes" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\InputCore\Classes" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\RHI\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\RenderCore\Public" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\Engine" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\InputCore" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\EngineSettings" ^
     dungeoneer\*.cpp ^
     unrealspy\*.cpp ^
     minhook-master\src\hook.c^
     minhook-master\src\buffer.c^
     minhook-master\src\trampoline.c^
     minhook-master\src\hde\hde64.c^
     imgui-1.78\imgui*.cpp^
     dungeoneer\imgui\*.cpp ^
     -link ^
      d3d11.lib d3dcompiler.lib ^
      -DLL /subsystem:console /DEBUG -OUT:dungeoneer.dll
