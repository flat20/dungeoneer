00007FF69C3D3D10 - 00007FF69A460000 = 1F73D10



struct FVector2D 
{
	/** Vector's X component. */
	float X;
	/** Vector's Y component. */
	float Y;
}

struct FLinearColor
{
	float	R,
			G,
			B,
			A;
}

________:00007FF69C3D3D10                         ; public: void UCanvas::K2_DrawBox(struct FVector2D, struct FVector2D, float, struct FLinearColor)
________:00007FF69C3D3D10                         ?K2_DrawBox@UCanvas@@QEAAXUFVector2D@@0MUFLinearColor@@@Z proc near
________:00007FF69C3D3D10                                                                 ; CODE XREF: sub_7FF69C439F80+135↓p
________:00007FF69C3D3D10                                                                 ; DATA XREF: ________:00007FF69DE8F1B8↓o ...
________:00007FF69C3D3D10
________:00007FF69C3D3D10                         var_78          = qword ptr -78h
________:00007FF69C3D3D10                         anonymous_2     = qword ptr -68h
________:00007FF69C3D3D10                         anonymous_0     = qword ptr -60h
________:00007FF69C3D3D10                         anonymous_1     = qword ptr -58h
________:00007FF69C3D3D10                         var_50          = byte ptr -50h
________:00007FF69C3D3D10                         anonymous_3     = qword ptr -48h
________:00007FF69C3D3D10                         var_40          = xmmword ptr -40h
________:00007FF69C3D3D10                         var_30          = qword ptr -30h
________:00007FF69C3D3D10                         var_28          = dword ptr -28h
________:00007FF69C3D3D10                         var_20          = qword ptr -20h
________:00007FF69C3D3D10                         anonymous_4     = qword ptr -18h
________:00007FF69C3D3D10                         var_8           = qword ptr -8
________:00007FF69C3D3D10                         arg_20          = qword ptr  28h
________:00007FF69C3D3D10
________:00007FF69C3D3D10 4C 8B DC                                mov     r11, rsp
________:00007FF69C3D3D13 48 81 EC 98 00 00 00                    sub     rsp, 98h
________:00007FF69C3D3D1A 66 49 0F 6E D0                          movq    xmm2, r8
________:00007FF69C3D3D1F 0F 57 C9                                xorps   xmm1, xmm1
________:00007FF69C3D3D22 0F 2F D1                                comiss  xmm2, xmm1
________:00007FF69C3D3D25 F2 0F 11 54 24 20                       movsd   [rsp+98h+var_78], xmm2
________:00007FF69C3D3D2B 0F 86 96 00 00 00                       jbe     loc_7FF69C3D3DC7
________:00007FF69C3D3D31 F3 0F 10 44 24 24                       movss   xmm0, dword ptr [rsp+98h+var_78+4]
________:00007FF69C3D3D37 0F 2F C1                                comiss  xmm0, xmm1
________:00007FF69C3D3D3A 0F 86 87 00 00 00                       jbe     loc_7FF69C3D3DC7
________:00007FF69C3D3D40
________:00007FF69C3D3D40                         loc_7FF69C3D3D40:                       ; DATA XREF: ________:00007FF69DE8F1B8↓o
________:00007FF69C3D3D40                                                                 ; ________:00007FF69DE8F1C8↓o ...
________:00007FF69C3D3D40 49 89 5B F8                             mov     [r11-8], rbx
________:00007FF69C3D3D44 48 8B 99 60 02 00 00                    mov     rbx, [rcx+260h]
________:00007FF69C3D3D4B 48 85 DB                                test    rbx, rbx
________:00007FF69C3D3D4E 74 6F                                   jz      short loc_7FF69C3D3DBF