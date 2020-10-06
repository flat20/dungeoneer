________:00007FF69B2D3560                         ; public: virtual void UObject::ProcessEvent(class UFunction *, void *)
________:00007FF69B2D3560                         ?ProcessEvent@UObject@@UEAAXPEAVUFunction@@PEAX@Z proc near
________:00007FF69B2D3560                                                                 ; CODE XREF: AActor::ProcessEvent(UFunction *,void *)+5F↓p
________:00007FF69B2D3560                                                                 ; DATA XREF: .dungeon:00007FF69F26EB68↓o
________:00007FF69B2D3560
________:00007FF69B2D3560                         var_120         = dword ptr -120h
________:00007FF69B2D3560                         var_100         = qword ptr -100h
________:00007FF69B2D3560                         var_F0          = dword ptr -0F0h
________:00007FF69B2D3560                         var_E0          = qword ptr -0E0h
________:00007FF69B2D3560                         var_D8          = word ptr -0D8h
________:00007FF69B2D3560                         var_D0          = qword ptr -0D0h
________:00007FF69B2D3560                         var_C8          = qword ptr -0C8h
________:00007FF69B2D3560                         var_C0          = qword ptr -0C0h
________:00007FF69B2D3560                         var_B8          = qword ptr -0B8h
________:00007FF69B2D3560                         var_B0          = xmmword ptr -0B0h
________:00007FF69B2D3560                         var_80          = qword ptr -80h
________:00007FF69B2D3560                         var_78          = qword ptr -78h
________:00007FF69B2D3560                         var_70          = xmmword ptr -70h
________:00007FF69B2D3560                         var_60          = qword ptr -60h
________:00007FF69B2D3560                         var_58          = qword ptr -58h
________:00007FF69B2D3560                         var_50          = byte ptr -50h
________:00007FF69B2D3560                         var_40          = qword ptr -40h
________:00007FF69B2D3560                         arg_18          = qword ptr  28h
________:00007FF69B2D3560
________:00007FF69B2D3560                         ; __unwind { // __GSHandlerCheck
________:00007FF69B2D3560 40 55                                   push    rbp
________:00007FF69B2D3562 56                                      push    rsi
________:00007FF69B2D3563 57                                      push    rdi
________:00007FF69B2D3564 41 54                                   push    r12
________:00007FF69B2D3566 41 55                                   push    r13
________:00007FF69B2D3568 41 56                                   push    r14
________:00007FF69B2D356A 41 57                                   push    r15
________:00007FF69B2D356C 48 81 EC F0 00 00 00                    sub     rsp, 0F0h
________:00007FF69B2D3573 48 8D 6C 24 30                          lea     rbp, [rsp+30h]
________:00007FF69B2D3578 48 89 9D 18 01 00 00                    mov     [rbp+0F0h+arg_18], rbx
________:00007FF69B2D357F 48 8B 05 C2 36 F3 02                    mov     rax, cs:__security_cookie
________:00007FF69B2D3586 48 33 C5                                xor     rax, rbp
________:00007FF69B2D3589 48 89 85 B0 00 00 00                    mov     [rbp+0F0h+var_40], rax
________:00007FF69B2D3590 8B 41 0C                                mov     eax, [rcx+0Ch]
________:00007FF69B2D3593 45 33 F6                                xor     r14d, r14d
________:00007FF69B2D3596 3B 05 F0 B4 13 03                       cmp     eax, dword ptr cs:qword_7FF69E40EA8C
________:00007FF69B2D359C 4D 8B F8                                mov     r15, r8
________:00007FF69B2D359F 48 8B F2                                mov     rsi, rdx
________:00007FF69B2D35A2 4C 8B E1                                mov     r12, rcx
________:00007FF69B2D35A5 41 B8 FF FF 00 00                       mov     r8d, 0FFFFh
________:00007FF69B2D35AB 7D 2A                                   jge     short loc_7FF69B2D35D7
________:00007FF69B2D35AD 99                                      cdq

40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC F0 00 00 00 48 8D 6C 24 30 48 89 9D 18 01 00 00

00007FF76C045250 - 00007FF76B1D0000 = E75250