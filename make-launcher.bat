
cl /nologo /EHsc ^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" ^
     launcher\main.cpp ^
     -link^
      /subsystem:console /DEBUG -OUT:dungeoneer.exe
