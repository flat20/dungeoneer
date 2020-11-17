
cl /nologo /EHsc ^
     /DFNAME_ANSICHAR ^
     /I minhook-master/include/ /I unrealspy/ /I unrealspy/4.22 ^
     /I imgui-1.78/  ^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared"  ^
     /FI C:\Users\andreas\code\dungeoneer\diet-ue\4.22\defines.h ^
     /I diet-ue/4.22/ ^
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
     /I "D:\UE_4.22\Engine\Source\Runtime\Launch\Resources" ^
     dungeoneer\*.cpp ^
     unrealspy\*.cpp ^
     unrealspy\4.22\console.cpp ^
     unrealspy\4.22\unreal_impl.cpp ^
     unrealspy\4.22\helpers.cpp ^
     diet-ue\4.22\impl.cpp ^
     minhook-master\src\hook.c^
     minhook-master\src\buffer.c^
     minhook-master\src\trampoline.c^
     minhook-master\src\hde\hde64.c^
     imgui-1.78\imgui*.cpp^
     dungeoneer\imgui\*.cpp ^
     -link ^
      d3d11.lib d3dcompiler.lib ^
      -DLL /subsystem:console /DEBUG -OUT:dungeoneer.dll

