
.text:0000000140690A30                         ; void __fastcall IncrementalPurgeGarbage(bool, float)
.text:0000000140690A30                         ?IncrementalPurgeGarbage@@YAX_NM@Z proc near
.text:0000000140690A30                                                                 ; CODE XREF: CollectGarbageInternal(EObjectFlags,bool)+D8↑p
.text:0000000140690A30                                                                 ; CollectGarbageInternal(EObjectFlags,bool)+1CA↑p ...
.text:0000000140690A30
.text:0000000140690A30                         PerformanceCount= LARGE_INTEGER ptr -0A8h
.text:0000000140690A30                         var_A0          = LARGE_INTEGER ptr -0A0h
.text:0000000140690A30                         var_98          = LARGE_INTEGER ptr -98h
.text:0000000140690A30                         var_90          = LARGE_INTEGER ptr -90h
.text:0000000140690A30                         var_88          = LARGE_INTEGER ptr -88h
.text:0000000140690A30                         var_80          = LARGE_INTEGER ptr -80h
.text:0000000140690A30                         var_78          = LARGE_INTEGER ptr -78h
.text:0000000140690A30                         var_68          = xmmword ptr -68h
.text:0000000140690A30                         var_58          = xmmword ptr -58h
.text:0000000140690A30                         var_48          = xmmword ptr -48h
.text:0000000140690A30                         var_38          = qword ptr -38h
.text:0000000140690A30                         var_30          = qword ptr -30h
.text:0000000140690A30                         var_28          = qword ptr -28h
.text:0000000140690A30                         var_20          = qword ptr -20h
.text:0000000140690A30                         var_18          = qword ptr -18h
.text:0000000140690A30                         var_10          = qword ptr -10h
.text:0000000140690A30                         arg_0           = qword ptr  8
.text:0000000140690A30                         arg_10          = byte ptr  18h
.text:0000000140690A30                         arg_18          = byte ptr  20h
.text:0000000140690A30
.text:0000000140690A30 41 54                                   push    r12
.text:0000000140690A32 48 81 EC C0 00 00 00                    sub     rsp, 0C0h
.text:0000000140690A39 44 0F B6 E1                             movzx   r12d, cl
.text:0000000140690A3D 44 0F 29 44 24 60                       movaps  [rsp+0C8h+var_68], xmm8
.text:0000000140690A43 48 8D 0D 16 D4 A9 01                    lea     rcx, aGarbagecollect ; "GarbageCollection"
.text:0000000140690A4A 44 0F 28 C1                             movaps  xmm8, xmm1
.text:0000000140690A4E E8 3D 54 EB FF                          call    ?BeginExclusiveStat@FCsvProfiler@@SAXPEBD@Z ; FCsvProfiler::BeginExclusiveStat(char const *)
.text:0000000140690A53 80 3D 6E 82 57 02 00                    cmp     cs:?GExitPurge@@3_NA, 0 ; bool GExitPurge
.text:0000000140690A5A 74 21                                   jz      short loc_140690A7D
.text:0000000140690A5C 48 8D 0D F5 E8 67 02                    lea     rcx, ?GUObjectArray@@3VFUObjectArray@@A ; this
.text:0000000140690A63 C6 05 F6 CD 67 02 01                    mov     cs:byte_142D0D860, 1

41 54 48 81 EC C0 00 00 00 44 0F B6 E1 44 0F 29 44 24 60 ?? ?? ?? ?? ?? ?? ?? 44 0F 28 C1

00007FF76F180B68 - 00007FF76B1D0000 = 3FB0B68