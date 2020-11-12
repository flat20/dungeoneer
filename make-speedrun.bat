
cl /nologo /EHsc ^
     /I launcher/ ^
     speedrun\main.cpp ^
     launcher\launcher.cpp ^
     -link^
      /subsystem:console -OUT:speedrun.exe

cl /nologo /EHsc ^
     /I minhook-master/include/ /I unrealspy/ ^
     /I imgui-1.78/  ^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared"  ^
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
     /I "D:\UE_4.22\Engine\Source\Runtime\AssetRegistry\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\ApplicationCore\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Renderer\Public" ^
     /I "D:\UE_4.22\Engine\Source" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Slate\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\AudioMixer\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\AudioPlatformConfiguration\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\AnimationCore\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Sockets\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\PacketHandlers\PacketHandler\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\NetworkReplayStreaming\NetworkReplayStreaming\Public" ^
     /I "D:\UE_4.22\Engine\Source\Runtime\Json\Public" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\Engine" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\InputCore" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\EngineSettings" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\SlateCore" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\AssetRegistry" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\Slate" ^
     /I "D:\UE_4.22\Engine\Intermediate\Build\Win64\UE4\Inc\AudioPlatformConfiguration" ^
     speedrun\dll.cpp speedrun\ui.cpp ^
     unrealspy\*.cpp ^
     diet-ue\*.cpp ^
     minhook-master\src\hook.c^
     minhook-master\src\buffer.c^
     minhook-master\src\trampoline.c^
     minhook-master\src\hde\hde64.c^
     imgui-1.78\imgui*.cpp^
     speedrun\imgui\*.cpp ^
     -link ^
      d3d11.lib d3dcompiler.lib ^
      -DLL /subsystem:console -OUT:speedrun.dll
