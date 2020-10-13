cl /nologo /EHsc ^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" ^
     launcher\*.cpp ^
     -link^
      /subsystem:console /DEBUG -OUT:dungeoneer.exe
