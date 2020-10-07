
cl /nologo /EHsc ^
     /I "%WindowsSdkDir%Include\um" /I "%WindowsSdkDir%Include\shared" ^
     inject\main.cpp ^
     -link^
      /subsystem:console /DEBUG -OUT:inject.exe
