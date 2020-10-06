
cl /nologo /EHsc ^
     /I dungeoneer/ /I unrealspy/ ^
     strid-mod/*.cpp ^
     unrealspy/util.cpp ^
     -link ^
      -DLL /subsystem:console /DEBUG -OUT:strid-mod.dll
