.text:000000014056C6A0                               ; void *__fastcall FWindowsPlatformProcess::GetDllHandle(const wchar_t *)
.text:000000014056C6A0                               ?GetDllHandle@FWindowsPlatformProcess@@SAPEAXPEB_W@Z proc near
.text:000000014056C6A0                                                                       ; CODE XREF: FOculusHMDModule::GetOVRPluginHandle(void)+1AF↑p
.text:000000014056C6A0                                                                       ; FSteamVRPlugin::LoadOpenVRModule(void)+25E↑p ...
.text:000000014056C6A0
.text:000000014056C6A0                               var_20          = qword ptr -20h
.text:000000014056C6A0                               var_18          = qword ptr -18h
.text:000000014056C6A0                               var_10          = qword ptr -10h
.text:000000014056C6A0                               var_8           = qword ptr -8
.text:000000014056C6A0                               OldMode         = dword ptr  20h
.text:000000014056C6A0                               arg_8           = qword ptr  28h
.text:000000014056C6A0                               arg_10          = qword ptr  30h
.text:000000014056C6A0                               arg_18          = qword ptr  38h
.text:000000014056C6A0
.text:000000014056C6A0 40 55                                         push    rbp
.text:000000014056C6A2 53                                            push    rbx
.text:000000014056C6A3 56                                            push    rsi
.text:000000014056C6A4 48 8B EC                                      mov     rbp, rsp
.text:000000014056C6A7 48 83 EC 40                                   sub     rsp, 40h
.text:000000014056C6AB 33 F6                                         xor     esi, esi
.text:000000014056C6AD
.text:000000014056C6AD                               loc_14056C6AD:                          ; DATA XREF: .rdata:000000014288A1F4↓o
.text:000000014056C6AD                                                                       ; .rdata:000000014288A208↓o ...
.text:000000014056C6AD 48 89 7C 24 68                                mov     [rsp+40h+arg_8], rdi
.text:000000014056C6B2
.text:000000014056C6B2                               loc_14056C6B2:                          ; DATA XREF: .rdata:000000014288A208↓o
.text:000000014056C6B2                                                                       ; .rdata:000000014288A21C↓o ...
.text:000000014056C6B2 4C 89 7C 24 78                                mov     [rsp+40h+arg_18], r15
.text:000000014056C6B7 4C 8B F9                                      mov     r15, rcx
.text:000000014056C6BA 48 8D 4D F0                                   lea     rcx, [rbp+var_10]

40 55 53 56 48 8B EC 48 83 EC 40 33 F6 48 89 7C 24 68 4C 89 7C 24 78 4C 8B F9 48 8D 4D F0