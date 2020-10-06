
cl /nologo /EHsc  ^
     /Iminhook-master\include\ /I ..\imgui-1.78^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include"  ^
     src\dll.cpp src\mcd.cpp src\unreal.cpp src\util.cpp src\ui.cpp ^
     minhook-master\src\hook.c^
     minhook-master\src\buffer.c^
     minhook-master\src\trampoline.c^
     minhook-master\src\hde\hde64.c^
     ..\imgui-1.78\imgui*.cpp src\imgui\imgui_impl_dx11.cpp src\imgui\imgui_impl_win32.cpp^
     -link impact.obj /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d11.lib d3dcompiler.lib^
      -DLL /subsystem:console /DEBUG -OUT:mcdstats.dll
