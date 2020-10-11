We get a reference to FConsoleManager by hooking ProcessUserConsoleInput and then executing a console command with
UConsole::ConsoleCommand

void __fastcall UConsole::ConsoleCommand(UConsole *this, const struct FString *a2)
this calls in to a few Exec() in 

else if( GEngine->Exec( InWorld, Cmd,Ar) )
  UnrealEngine.cpp
        
    bool UEngine::Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar )
    {

      	else if(IConsoleManager::Get().ProcessUserConsoleInput(Cmd, Ar, InWorld))
        {
          // console variable interaction (get value, set value or get help)
          return true;
        }

      SO if we hook ProcessUserConsoleInput and run a console command that's not caught by other things
      eventually it should reach ProcessUserConsoleInput


.text:0000000140469070                         ; bool FConsoleManager::ProcessUserConsoleInput(FConsoleManager *__hidden this, const wchar_t *, struct FOutputDevice *, struct UWorld *)
.text:0000000140469070                         ?ProcessUserConsoleInput@FConsoleManager@@UEAA_NPEB_WAEAVFOutputDevice@@PEAVUWorld@@@Z proc near
.text:0000000140469070                                                                 ; DATA XREF: .rdata:00000001420F15A0↓o
.text:0000000140469070                                                                 ; .rdata:000000014287A478↓o ...

...

.text:0000000140469070
.text:0000000140469070 48 8B C4                                mov     rax, rsp
.text:0000000140469073 4C 89 48 20                             mov     [rax+20h], r9
.text:0000000140469077 4C 89 40 18                             mov     [rax+18h], r8
.text:000000014046907B 48 89 48 08                             mov     [rax+8], rcx
.text:000000014046907F 55                                      push    rbp
.text:0000000140469080 56                                      push    rsi
.text:0000000140469081 48 8D 68 A1                             lea     rbp, [rax-5Fh]
.text:0000000140469085 48 81 EC B8 00 00 00                    sub     rsp, 0B8h
.text:000000014046908C 33 F6                                   xor     esi, esi
.text:000000014046908E
.text:000000014046908E                         loc_14046908E:                          ; DATA XREF: .rdata:000000014287A478↓o
.text:000000014046908E                                                                 ; .rdata:000000014287A488↓o ...
.text:000000014046908E 48 89 58 E8                             mov     [rax-18h], rbx
.text:0000000140469092 48 8B DA                                mov     rbx, rdx
.text:0000000140469095 48 89 78 E0                             mov     [rax-20h], rdi

48 8B C4 4C 89 48 20 4C 89 40 18 48 89 48 08 55 56 48 8D 68 A1 48 81 EC B8 00 00 00 33 F6
00007FF76BDCFAF0 - 00007FF76B1D0000 = 0xBFFAF0

.text:00000001417E49D0                         ; void __fastcall UConsole::ConsoleCommand(UConsole *__hidden this, const struct FString *)
.text:00000001417E49D0                         ?ConsoleCommand@UConsole@@UEAAXAEBVFString@@@Z proc near
.text:00000001417E49D0                                                                 ; DATA XREF: .rdata:0000000142549E60↓o
.text:00000001417E49D0                                                                 ; .pdata:0000000142F986A0↓o
.text:00000001417E49D0
.text:00000001417E49D0                         var_18          = qword ptr -18h
.text:00000001417E49D0                         arg_0           = qword ptr  8
.text:00000001417E49D0                         arg_8           = qword ptr  10h
.text:00000001417E49D0                         arg_10          = qword ptr  18h
.text:00000001417E49D0                         arg_18          = qword ptr  20h
.text:00000001417E49D0
.text:00000001417E49D0 48 89 5C 24 10                          mov     [rsp+arg_8], rbx
.text:00000001417E49D5 48 89 6C 24 18                          mov     [rsp+arg_10], rbp
.text:00000001417E49DA 48 89 74 24 20                          mov     [rsp+arg_18], rsi
.text:00000001417E49DF 57                                      push    rdi
.text:00000001417E49E0 48 83 EC 30                             sub     rsp, 30h
.text:00000001417E49E4 48 8B F2                                mov     rsi, rdx
.text:00000001417E49E7 48 89 54 24 40                          mov     [rsp+38h+arg_0], rdx
.text:00000001417E49EC 48 8B D9                                mov     rbx, rcx
.text:00000001417E49EF 48 8D 54 24 40                          lea     rdx, [rsp+38h+arg_0]
.text:00000001417E49F4 48 83 C1 68                             add     rcx, 68h ; 'h'

48 89 5C 24 10 48 89 6C 24 18 48 89 74 24 20 57 48 83 EC 30 48 8B F2 48 89 54 24 40 48 8B D9 48 8D 54 24 40 48 83 C1 68