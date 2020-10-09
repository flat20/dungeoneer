.text:00000001406E88B0                         ; class UObject * StaticConstructObject_Internal(class UClass *, class UObject *, class FName, enum  EObjectFlags, enum  EInternalObjectFlags, class UObject *, bool, struct FObjectInstancingGraph *, bool)
.text:00000001406E88B0                         ?StaticConstructObject_Internal@@YAPEAVUObject@@PEAVUClass@@PEAV1@VFName@@W4EObjectFlags@@W4EInternalObjectFlags@@1_NPEAUFObjectInstancingGraph@@5@Z proc near
.text:00000001406E88B0                                                                 ; CODE XREF: NewObject<UUserWidget>(UObject *,UClass *,FName,EObjectFlags,UObject *,bool,FObjectInstancingGraph *)+82↑p
.text:00000001406E88B0                                                                 ; FEngineLoop::PreInit(wchar_t const *)+33AC↑p ...
.text:00000001406E88B0
.text:00000001406E88B0                         var_1C0         = dword ptr -1C0h
.text:00000001406E88B0                         var_1B8         = byte ptr -1B8h
.text:00000001406E88B0                         var_1B0         = qword ptr -1B0h
.text:00000001406E88B0                         var_1A0         = byte ptr -1A0h
.text:00000001406E88B0                         var_19F         = byte ptr -19Fh
.text:00000001406E88B0                         var_198         = qword ptr -198h
.text:00000001406E88B0                         var_190         = qword ptr -190h
.text:00000001406E88B0                         var_188         = qword ptr -188h
.text:00000001406E88B0                         var_180         = qword ptr -180h
.text:00000001406E88B0                         var_178         = byte ptr -178h
.text:00000001406E88B0                         var_177         = word ptr -177h
.text:00000001406E88B0                         var_170         = qword ptr -170h
.text:00000001406E88B0                         var_E8          = qword ptr -0E8h
.text:00000001406E88B0                         var_E0          = qword ptr -0E0h
.text:00000001406E88B0                         var_58          = qword ptr -58h
.text:00000001406E88B0                         var_50          = qword ptr -50h
.text:00000001406E88B0                         var_48          = qword ptr -48h
.text:00000001406E88B0                         var_40          = byte ptr -40h
.text:00000001406E88B0                         var_38          = qword ptr -38h
.text:00000001406E88B0                         arg_20          = dword ptr  30h
.text:00000001406E88B0                         arg_28          = qword ptr  38h
.text:00000001406E88B0                         arg_30          = byte ptr  40h
.text:00000001406E88B0                         arg_38          = qword ptr  48h
.text:00000001406E88B0                         arg_40          = byte ptr  50h
.text:00000001406E88B0
.text:00000001406E88B0                         ; __unwind { // __GSHandlerCheck
.text:00000001406E88B0 40 55                                   push    rbp
.text:00000001406E88B2 53                                      push    rbx
.text:00000001406E88B3 56                                      push    rsi
.text:00000001406E88B4 57                                      push    rdi
.text:00000001406E88B5 41 54                                   push    r12
.text:00000001406E88B7 41 56                                   push    r14
.text:00000001406E88B9 41 57                                   push    r15
.text:00000001406E88BB 48 8D AC 24 50 FF FF FF                 lea     rbp, [rsp-0B0h]
.text:00000001406E88C3 48 81 EC B0 01 00 00                    sub     rsp, 1B0h
.text:00000001406E88CA 48 8B 05 07 8B 4D 02                    mov     rax, cs:__security_cookie
.text:00000001406E88D1 48 33 C4                                xor     rax, rsp
.text:00000001406E88D4 48 89 85 A8 00 00 00                    mov     [rbp+0E0h+var_38], rax
.text:00000001406E88DB F7 81 B4 00 00 00 80 00+                test    dword ptr [rcx+0B4h], 10000080h
.text:00000001406E88E5 45 8B F9                                mov     r15d, r9d
.text:00000001406E88E8 44 8B A5 10 01 00 00                    mov     r12d, [rbp+0E0h+arg_20]
.text:00000001406E88EF 49 8B D8                                mov     rbx, r8

40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 50 FF FF FF 48 81 EC B0 01 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 A8 00 00 00