________:00007FF69C0497B0                         ; public: virtual void AHUD::PostRender(void)
________:00007FF69C0497B0                         ?PostRender@AHUD@@UEAAXXZ proc near     ; CODE XREF: ________:00007FF69BFAA620↑j
________:00007FF69C0497B0                                                                 ; DATA XREF: ________:00007FF69DE598CC↓o ...
________:00007FF69C0497B0
________:00007FF69C0497B0                         var_B0          = qword ptr -0B0h
________:00007FF69C0497B0                         var_A0          = xmmword ptr -0A0h
________:00007FF69C0497B0                         var_90          = xmmword ptr -90h
________:00007FF69C0497B0                         var_80          = xmmword ptr -80h
________:00007FF69C0497B0                         var_70          = xmmword ptr -70h
________:00007FF69C0497B0                         var_60          = qword ptr -60h
________:00007FF69C0497B0                         var_58          = xmmword ptr -58h
________:00007FF69C0497B0                         var_40          = xmmword ptr -40h
________:00007FF69C0497B0                         var_30          = qword ptr -30h
________:00007FF69C0497B0                         var_28          = qword ptr -28h
________:00007FF69C0497B0                         var_20          = qword ptr -20h
________:00007FF69C0497B0                         var_18          = qword ptr -18h
________:00007FF69C0497B0                         var_10          = qword ptr -10h
________:00007FF69C0497B0                         arg_0           = qword ptr  10h
________:00007FF69C0497B0                         arg_8           = qword ptr  18h
________:00007FF69C0497B0                         arg_10          = qword ptr  20h
________:00007FF69C0497B0
________:00007FF69C0497B0 40 55                                   push    rbp
________:00007FF69C0497B2 56                                      push    rsi
________:00007FF69C0497B3 48 8D 6C 24 B1                          lea     rbp, [rsp-4Fh]
________:00007FF69C0497B8 48 81 EC C8 00 00 00                    sub     rsp, 0C8h
________:00007FF69C0497BF 48 8B 01                                mov     rax, [rcx]
________:00007FF69C0497C2 48 8B F1                                mov     rsi, rcx
________:00007FF69C0497C5 FF 90 40 01 00 00                       call    qword ptr [rax+140h]
________:00007FF69C0497CB 48 85 C0                                test    rax, rax
________:00007FF69C0497CE 0F 84 86 07 00 00                       jz      loc_7FF69C049F5A
________:00007FF69C0497D4 48 83 BE 80 03 00 00 00                 cmp     qword ptr [rsi+380h], 0
________:00007FF69C0497DC 0F 84 78 07 00 00                       jz      loc_7FF69C049F5A

40 55 56 48 8D 6C 24 B1 48 81 EC C8 00 00 00 48 8B 01 48 8B F1

00007FF76CDBB4B0 - 00007FF76B1D0000 = 1BEB4B0