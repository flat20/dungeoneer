ml64 /Fo impact.obj /c src\impact.asm

cl /EHsc /Iminhook-master\include\ src\main.cpp^
     minhook-master\src\hook.c^
     minhook-master\src\buffer.c^
     minhook-master\src\trampoline.c^
     minhook-master\src\hde\hde64.c^
     -link /subsystem:console /DEBUG:FULL -OUT:mcdstats.exe

cl /EHsc /Iminhook-master\include\ src\dll.cpp^
    minhook-master\src\hook.c^
    minhook-master\src\buffer.c^
    minhook-master\src\trampoline.c^
    minhook-master\src\hde\hde64.c^
    -link impact.obj -DLL /subsystem:console -OUT:mcdstats.dll
