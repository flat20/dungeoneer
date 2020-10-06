
cl /nologo /EHsc ^
     /I minhook-master\include\ /I unrealspy\ ^
     /I ../imgui-1.78  ^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" /I "%DXSDK_DIR%Include"  ^
     dungeoneer\*.cpp ^
     unrealspy\*.cpp ^
     minhook-master\src\hook.c^
     minhook-master\src\buffer.c^
     minhook-master\src\trampoline.c^
     minhook-master\src\hde\hde64.c^
     ..\imgui-1.78\imgui*.cpp^
     dungeoneer\imgui\*.cpp ^
     -link ^
      /LIBPATH:"%DXSDK_DIR%/Lib/x86" d3d11.lib d3dcompiler.lib ^
      -DLL /subsystem:console /DEBUG -OUT:dungeoneer.dll
