cl /nologo /EHsc ^
     /I dungeoneer/ /I unrealspy/ ^
     /I imgui-1.78/  ^
     debug-mod\*.cpp ^
     unrealspy/util.cpp ^
     imgui-1.78\imgui*.cpp^
     -link ^
      -DLL /subsystem:console /DEBUG -OUT:debug-mod.dll
