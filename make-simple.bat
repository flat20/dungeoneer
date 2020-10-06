
cl /nologo /EHsc ^
     /I dungeoneer/ /I unrealspy/ ^
     simple-mod/*.cpp ^
     unrealspy/util.cpp ^
     -link ^
      -DLL /subsystem:console /DEBUG -OUT:simple-mod.dll
