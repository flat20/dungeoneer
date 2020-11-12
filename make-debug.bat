cl /nologo /EHsc ^
     /I dungeoneer/ /I unrealspy/ ^
     /I imgui-1.78/  ^
     /FI C:\Users\andreas\code\dungeoneer\diet-ue\defines.h ^
     /I diet-ue/ ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Core\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Core\Private" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\CoreUObject\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Engine\Classes" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Engine\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\EngineSettings\Classes" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\InputCore\Classes" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\RHI\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\RenderCore\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\SlateCore\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\ApplicationCore\Public" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\Engine" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\InputCore" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\EngineSettings" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\SlateCore" ^
     debug-mod\*.cpp ^
     unrealspy/util.cpp ^
     imgui-1.78\imgui*.cpp^
     -link ^
      -DLL /subsystem:console /DEBUG -OUT:debug-mod.dll
