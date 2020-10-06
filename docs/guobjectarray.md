
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


This instantiates itself with a reference to the global GUObjectArray. So can we create our own version, store the reference to GUObjectArray
and then delete it?
FRawObjectIterator(bool bOnlyGCedObjects = false) :
	FUObjectArray::TIterator( GUObjectArray, bOnlyGCedObjects )
	{
	}

.text:000000014067D020                         ; FRawObjectIterator *__fastcall FRawObjectIterator::FRawObjectIterator(FRawObjectIterator *__hidden this, bool)
.text:000000014067D020                         ??0FRawObjectIterator@@QEAA@_N@Z proc near
.text:000000014067D020                                                                 ; CODE XREF: IncrementalPurgeGarbage(bool,float)+1A0↓p
.text:000000014067D020                                                                 ; IncrementalPurgeGarbage(bool,float)+5AA↓p
.text:000000014067D020 84 D2                                   test    dl, dl
.text:000000014067D022 48 C7 41 10 00 00 00 00                 mov     qword ptr [rcx+10h], 0
.text:000000014067D02A B8 FF FF FF FF                          mov     eax, 0FFFFFFFFh
.text:000000014067D02F 4C 8D 05 22 23 69 02                    lea     r8, ?GUObjectArray@@3VFUObjectArray@@A ; FUObjectArray GUObjectArray
.text:000000014067D036 89 41 08                                mov     [rcx+8], eax
.text:000000014067D039 4C 8B D1                                mov     r10, rcx
.text:000000014067D03C 4C 89 01                                mov     [rcx], r8
.text:000000014067D03F 0F 45 05 16 23 69 02                    cmovnz  eax, cs:dword_142D0F35C
.text:000000014067D046 FF C0                                   inc     eax
.text:000000014067D048 89 41 08                                mov     [rcx+8], eax
.text:000000014067D04B 3B 05 2B 23 69 02                       cmp     eax, dword ptr cs:qword_142D0F37C
.text:000000014067D051 7D 4C                                   jge     short loc_14067D09F
.text:000000014067D053
.text:000000014067D053                         loc_14067D053:                          ; CODE XREF: FRawObjectIterator::FRawObjectIterator(bool)+75↓j
.text:000000014067D053 0F B7 D0                                movzx   edx, ax
.text:000000014067D056 8B C8                                   mov     ecx, eax
.text:000000014067D058 85 C0                                   test    eax, eax
.text:000000014067D05A 79 0C                                   jns     short loc_14067D068
.text:000000014067D05C 8D 88 FF FF 00 00                       lea     ecx, [rax+0FFFFh]
.text:000000014067D062 81 EA 00 00 01 00                       sub     edx, 10000h

84 D2 48 C7 41 10 00 00 00 00 B8 FF FF FF FF ?? ?? ?? ?? ?? ?? ?? 89 41 08 4C 8B D1 4C 89 01

00007FF76BFDF6F0 - 00007FF76B1D0000 = E0F6F0