
cl /nologo /EHsc  ^
     /I minhook-master/include/ /I imgui-1.78/ /I unrealspy/^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared"  ^
     console\*.cpp ^
     console\imgui\*.cpp ^
     unrealspy\*.cpp ^
     minhook-master\src\hook.c^
     minhook-master\src\buffer.c^
     minhook-master\src\trampoline.c^
     minhook-master\src\hde\hde64.c^
     imgui-1.78\imgui*.cpp^
     -link d3d11.lib d3dcompiler.lib^
      -DLL /subsystem:console /DEBUG -OUT:console.dll
