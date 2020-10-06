
.text:000000014145A4A0                               ; void __fastcall AHUD::PostRender(AHUD *__hidden this)
.text:000000014145A4A0                               ?PostRender@AHUD@@UEAAXXZ proc near     ; CODE XREF: ADebugCameraHUD::PostRender(void)↑j
.text:000000014145A4A0                                                                       ; DATA XREF: .rdata:00000001424C0C08↓o ...
.text:000000014145A4A0
.text:000000014145A4A0                               var_B0          = qword ptr -0B0h
.text:000000014145A4A0                               var_A0          = xmmword ptr -0A0h
.text:000000014145A4A0                               var_90          = xmmword ptr -90h
.text:000000014145A4A0                               var_80          = xmmword ptr -80h
.text:000000014145A4A0                               var_70          = xmmword ptr -70h
.text:000000014145A4A0                               var_60          = qword ptr -60h
.text:000000014145A4A0                               var_58          = xmmword ptr -58h
.text:000000014145A4A0                               var_40          = xmmword ptr -40h
.text:000000014145A4A0                               var_30          = qword ptr -30h
.text:000000014145A4A0                               var_28          = qword ptr -28h
.text:000000014145A4A0                               var_20          = qword ptr -20h
.text:000000014145A4A0                               var_18          = qword ptr -18h
.text:000000014145A4A0                               var_10          = qword ptr -10h
.text:000000014145A4A0                               arg_0           = qword ptr  10h
.text:000000014145A4A0                               arg_8           = qword ptr  18h
.text:000000014145A4A0                               arg_10          = qword ptr  20h
.text:000000014145A4A0
.text:000000014145A4A0 40 55                                         push    rbp
.text:000000014145A4A2 56                                            push    rsi
.text:000000014145A4A3 48 8D 6C 24 B1                                lea     rbp, [rsp-4Fh]
.text:000000014145A4A8 48 81 EC C8 00 00 00                          sub     rsp, 0C8h
.text:000000014145A4AF 48 8B 01                                      mov     rax, [rcx]
.text:000000014145A4B2 48 8B F1                                      mov     rsi, rcx
.text:000000014145A4B5 FF 90 40 01 00 00                             call    qword ptr [rax+140h]
.text:000000014145A4BB 48 85 C0                                      test    rax, rax
.text:000000014145A4BE 0F 84 86 07 00 00                             jz      loc_14145AC4A
.text:000000014145A4C4 48 83 BE 80 03 00 00 00                       cmp     qword ptr [rsi+380h], 0
.text:000000014145A4CC 0F 84 78 07 00 00                             jz      loc_14145AC4A
.text:000000014145A4D2 48 8B 06                                      mov     rax, [rsi]
.text:000000014145A4D5 48 8B CE                                      mov     rcx, rsi


40 55 56 48 8D 6C 24 B1 48 81 EC C8 00 00 00 48 8B 01 48 8B F1 
00007FF69C0497B0 - 00007FF69A460000 = 1BE97B0

.text:000000014144D6F0                               ; void __stdcall __high AHUD::DrawRect(struct FLinearColor, float, float, float, float)
.text:000000014144D6F0                               ?DrawRect@AHUD@@QEAAXUFLinearColor@@MMMM@Z proc near
.text:000000014144D6F0                                                                       ; CODE XREF: AHUD::execDrawRect(UObject *,FFrame &,void * const)+194↓p
.text:000000014144D6F0                                                                       ; DATA XREF: .pdata:0000000142F67368↓o
.text:000000014144D6F0
.text:000000014144D6F0                               var_C8          = qword ptr -0C8h
.text:000000014144D6F0                               var_B8          = dword ptr -0B8h
.text:000000014144D6F0                               var_B4          = dword ptr -0B4h
.text:000000014144D6F0                               var_B0          = dword ptr -0B0h
.text:000000014144D6F0                               var_AC          = dword ptr -0ACh
.text:000000014144D6F0                               var_A8          = byte ptr -0A8h
.text:000000014144D6F0                               var_94          = dword ptr -94h
.text:000000014144D6F0                               var_8           = byte ptr -8
.text:000000014144D6F0                               arg_20          = dword ptr  28h
.text:000000014144D6F0                               arg_28          = dword ptr  30h
.text:000000014144D6F0
.text:000000014144D6F0 48 8B C4                                      mov     rax, rsp
.text:000000014144D6F3 48 89 58 08                                   mov     [rax+8], rbx
.text:000000014144D6F7 57                                            push    rdi
.text:000000014144D6F8 48 81 EC E0 00 00 00                          sub     rsp, 0E0h
.text:000000014144D6FF 0F 29 70 E8                                   movaps  xmmword ptr [rax-18h], xmm6
.text:000000014144D703 48 8B FA                                      mov     rdi, rdx
.text:000000014144D706 0F 29 78 D8                                   movaps  xmmword ptr [rax-28h], xmm7
.text:000000014144D70A 0F 28 F3                                      movaps  xmm6, xmm3
.text:000000014144D70D 0F 28 FA                                      movaps  xmm7, xmm2
.text:000000014144D710 48 8B D9                                      mov     rbx, rcx

48 8B C4 48 89 58 08 57 48 81 EC E0 00 00 00 0F 29 70 E8 48 8B FA 0F 29 78 D8 0F 28 F3 0F 28 FA 48 8B D9

00007FF69C035480 - 00007FF69A460000 = 1BD5480

.text:000000014144D7A0                               ; void __stdcall __high AHUD::DrawText(const struct FString *, struct FLinearColor, float, float, struct UFont *, float, bool)
.text:000000014144D7A0                               ?DrawText@AHUD@@QEAAXAEBVFString@@UFLinearColor@@MMPEAVUFont@@M_N@Z proc near
.text:000000014144D7A0                                                                       ; CODE XREF: AHUD::execDrawText(UObject *,FFrame &,void * const)+1EC↓p
.text:000000014144D7A0                                                                       ; DATA XREF: .rdata:000000014294B5E0↓o ...
.text:000000014144D7A0
.text:000000014144D7A0                               var_228         = qword ptr -228h
.text:000000014144D7A0                               var_218         = dword ptr -218h
.text:000000014144D7A0                               var_214         = dword ptr -214h
.text:000000014144D7A0                               var_210         = byte ptr -210h
.text:000000014144D7A0                               var_208         = qword ptr -208h
.text:000000014144D7A0                               var_1F8         = byte ptr -1F8h
.text:000000014144D7A0                               var_158         = dword ptr -158h
.text:000000014144D7A0                               var_154         = dword ptr -154h
.text:000000014144D7A0                               var_50          = qword ptr -50h
.text:000000014144D7A0                               var_48          = xmmword ptr -48h
.text:000000014144D7A0                               var_38          = xmmword ptr -38h
.text:000000014144D7A0                               var_28          = xmmword ptr -28h
.text:000000014144D7A0                               arg_18          = qword ptr  20h
.text:000000014144D7A0                               arg_20          = dword ptr  28h
.text:000000014144D7A0                               arg_28          = qword ptr  30h
.text:000000014144D7A0                               arg_30          = dword ptr  38h
.text:000000014144D7A0                               arg_38          = byte ptr  40h
.text:000000014144D7A0
.text:000000014144D7A0                               ; __unwind { // __GSHandlerCheck
.text:000000014144D7A0 40 55                                         push    rbp
.text:000000014144D7A2 56                                            push    rsi
.text:000000014144D7A3 57                                            push    rdi
.text:000000014144D7A4 48 81 EC 30 02 00 00                          sub     rsp, 230h
.text:000000014144D7AB 44 0F 29 84 24 00 02 00 00                    movaps  [rsp+248h+var_48], xmm8
.text:000000014144D7B4 48 8B 05 1D 3C 77 01                          mov     rax, cs:__security_cookie
.text:000000014144D7BB 48 33 C4                                      xor     rax, rsp
.text:000000014144D7BE 48 89 84 24 F8 01 00 00                       mov     [rsp+248h+var_50], rax
.text:000000014144D7C6 44 0F 28 C3                                   movaps  xmm8, xmm3
.text:000000014144D7CA 49 8B E8                                      mov     rbp, r8
.text:000000014144D7CD 48 8B FA                                      mov     rdi, rdx
.text:000000014144D7D0 48 8B F1                                      mov     rsi, rcx

40 55 56 57 48 81 EC 30 02 00 00 44 0F 29 84 24 00 02 00 00

00007FF69C035530 - 00007FF69A460000 = 1BD5530


.text:0000000141456EC0                               ; void __fastcall AHUD::GetTextSize(AHUD *__hidden this, const struct FString *, float *, float *, struct UFont *, float)
.text:0000000141456EC0                               ?GetTextSize@AHUD@@QEBAXAEBVFString@@AEAM1PEAVUFont@@M@Z proc near
.text:0000000141456EC0                                                                       ; CODE XREF: AHUD::execGetTextSize(UObject *,FFrame &,void * const)+1A8↓p
.text:0000000141456EC0                                                                       ; DATA XREF: .pdata:0000000142F679B0↓o
.text:0000000141456EC0
.text:0000000141456EC0                               var_28          = qword ptr -28h
.text:0000000141456EC0                               var_20          = dword ptr -20h
.text:0000000141456EC0                               var_18          = dword ptr -18h
.text:0000000141456EC0                               arg_0           = qword ptr  8
.text:0000000141456EC0                               arg_8           = qword ptr  10h
.text:0000000141456EC0                               arg_10          = qword ptr  18h
.text:0000000141456EC0                               arg_20          = qword ptr  28h
.text:0000000141456EC0                               arg_28          = dword ptr  30h
.text:0000000141456EC0
.text:0000000141456EC0 48 89 5C 24 08                                mov     [rsp+arg_0], rbx
.text:0000000141456EC5 48 89 6C 24 10                                mov     [rsp+arg_8], rbp
.text:0000000141456ECA 48 89 74 24 18                                mov     [rsp+arg_10], rsi
.text:0000000141456ECF 57                                            push    rdi
.text:0000000141456ED0 48 83 EC 40                                   sub     rsp, 40h
.text:0000000141456ED4 49 8B F9                                      mov     rdi, r9
.text:0000000141456ED7 49 8B F0                                      mov     rsi, r8
.text:0000000141456EDA 48 8B EA                                      mov     rbp, rdx
.text:0000000141456EDD 48 8B D9                                      mov     rbx, rcx
.text:0000000141456EE0 E8 9B 16 00 00                                call    ?IsCanvasValid_WarnIfNot@AHUD@@IEBA_NXZ ; #STR: "Canvas Draw functions may only be called during the handli, "PIE_Warning_Message_CanvasCallOutsideOfDrawCanvas"
.text:0000000141456EE5 84 C0                                         test    al, al

48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 40 49 8B F9 49 8B F0 48 8B EA 48 8B D9 ?? ?? ?? ?? ?? 84 C0
00007FF69C044650 - 00007FF69A460000 = 1BE4650

UEngine Engine.h has a lot of font related stuff. Maybe that can be used?

class ENGINE_API UEngine
	: public UObject
	, public FExec

UObject so it can be found in the list?

Default__Engine (Engine)
Find it by name Default__Engine

also found this:
Default__GameEngine (GameEngine)
GameEngine (GameEngine)
attach dll 7ff6ae600000 7ff6ae600000
EntryPoint: 7ff6b3828058 BaseOfDll 7ff6ae600000 SizeOfImage 59e3000
Mem State Commit true
Mem Protect PAGE_NOACCESS false
drawbox: 7ff6b0573d10
drawrect: 7ff6b01d5480
drawtext: 7ff6b01d5530
Num: 505941
Default__Font FName 128456.0 InternalIndex: 46894  Class: Font FName 24336.0 InternalIndex: 2030
Default__FontFace FName 128457.0 InternalIndex: 46895  Class: FontFace FName 24337.0 InternalIndex: 2031
Default__FontImportOptions FName 128458.0 InternalIndex: 46896  Class: FontImportOptions FName 24338.0 InternalIndex: 2032
Default__MaterialExpressionFontSample FName 128758.0 InternalIndex: 47121  Class: MaterialExpressionFontSample FName 25810.0 InternalIndex: 2233
Default__MaterialExpressionFontSampleParameter FName 128759.0 InternalIndex: 47122  Class: MaterialExpressionFontSampleParameter FName 25811.0 InternalIndex: 2234
RobotoDistanceField FName 103374.0 InternalIndex: 47577  Class: Font FName 24336.0 InternalIndex: 2030
MaterialExpressionFontSampleParameter FName 25811.1 InternalIndex: 47581  Class: MaterialExpressionFontSampleParameter FName 25811.0 InternalIndex: 2234
NotoSansKR-Bold FName 94015.0 InternalIndex: 48893  Class: FontFace FName 24337.0 InternalIndex: 2031
SlateArrowCount FName 94028.0 InternalIndex: 48894  Class: Font FName 24336.0 InternalIndex: 2030
PlayerName FName 94025.0 InternalIndex: 48896  Class: Font FName 24336.0 InternalIndex: 2030
MinecraftTen FName 93991.0 InternalIndex: 48899  Class: FontFace FName 24337.0 InternalIndex: 2031
LocalPlayerDisplayTextFont FName 94022.0 InternalIndex: 48900  Class: Font FName 24336.0 InternalIndex: 2030
Default__FontBulkData FName 131342.0 InternalIndex: 49897  Class: FontBulkData FName 22783.0 InternalIndex: 1436
Default__FontFaceInterface FName 131343.0 InternalIndex: 49898  Class: FontFaceInterface FName 22784.0 InternalIndex: 1437
Default__FontProviderInterface FName 131344.0 InternalIndex: 49899  Class: FontProviderInterface FName 22785.0 InternalIndex: 1438
RobotoRegular FName 103393.0 InternalIndex: 50193  Class: FontFace FName 24337.0 InternalIndex: 2031
RobotoLight FName 103390.0 InternalIndex: 50194  Class: FontFace FName 24337.0 InternalIndex: 2031
RobotoItalic FName 103387.0 InternalIndex: 50195  Class: FontFace FName 24337.0 InternalIndex: 2031
RobotoBoldItalic FName 103384.0 InternalIndex: 50196  Class: FontFace FName 24337.0 InternalIndex: 2031
RobotoBold FName 103381.0 InternalIndex: 50197  Class: FontFace FName 24337.0 InternalIndex: 2031
Roboto FName 103371.0 InternalIndex: 50198  Class: Font FName 24336.0 InternalIndex: 2030
RobotoTiny FName 103377.0 InternalIndex: 50710  Class: FontFace FName 24337.0 InternalIndex: 2031
RobotoTiny FName 103377.0 InternalIndex: 50711  Class: Font FName 24336.0 InternalIndex: 2030
MinecraftSeven FName 93985.0 InternalIndex: 53670  Class: FontFace FName 24337.0 InternalIndex: 2031
NewSeven FName 93997.0 InternalIndex: 54254  Class: Font FName 24336.0 InternalIndex: 2030
NotoSans FName 94006.0 InternalIndex: 74832  Class: Font FName 24336.0 InternalIndex: 2030
NotoSansKR-Regular FName 94018.0 InternalIndex: 75238  Class: FontFace FName 24337.0 InternalIndex: 2031
MinecraftFiveBold FName 93982.0 InternalIndex: 75239  Class: FontFace FName 24337.0 InternalIndex: 2031
MinecraftFive FName 93979.0 InternalIndex: 75240  Class: FontFace FName 24337.0 InternalIndex: 2031
NewFive FName 93994.0 InternalIndex: 75465  Class: Font FName 24336.0 InternalIndex: 2030
NotoSansCJKjp-Regular FName 94012.0 InternalIndex: 75490  Class: FontFace FName 24337.0 InternalIndex: 2031
NotoSansCJKjp-Bold FName 94009.0 InternalIndex: 75491  Class: FontFace FName 24337.0 InternalIndex: 2031
NotoSans-Regular FName 94003.0 InternalIndex: 75492  Class: FontFace FName 24337.0 InternalIndex: 2031
NotoSans-Bold FName 94000.0 InternalIndex: 75493  Class: FontFace FName 24337.0 InternalIndex: 2031
MinecraftSymbol FName 93988.0 InternalIndex: 75494  Class: FontFace FName 24337.0 InternalIndex: 2031
Minecraft FName 93976.0 InternalIndex: 78030  Class: Font FName 24336.0 InternalIndex: 2030
last index: 505941
Num: 505941
seven: NewSeven Font
added CalculateBaseMagnitude
InitMcd Done
Attached and ready.


