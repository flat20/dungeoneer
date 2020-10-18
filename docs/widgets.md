

.text:000000014104CFD0                         ; class UUserWidget * CreateWidget<class UUserWidget, class UWorld>(class UWorld *, class TSubclassOf<class UUserWidget>, class FName)
.text:000000014104CFD0                         ??$CreateWidget@VUUserWidget@@VUWorld@@@@YAPEAVUUserWidget@@PEAVUWorld@@V?$TSubclassOf@VUUserWidget@@@@VFName@@@Z proc near
.text:000000014104CFD0                                                                 ; CODE XREF: UWidgetBlueprintLibrary::Create(UObject *,TSubclassOf<UUserWidget>,APlayerController *)+E5↓j
.text:000000014104CFD0                                                                 ; UMenuAnchor::HandleGetMenuContent(void)+186↓p ...
.text:000000014104CFD0
.text:000000014104CFD0                         var_18          = qword ptr -18h
.text:000000014104CFD0                         arg_0           = qword ptr  8
.text:000000014104CFD0                         arg_8           = qword ptr  10h
.text:000000014104CFD0                         arg_10          = qword ptr  18h
.text:000000014104CFD0
.text:000000014104CFD0 48 89 5C 24 10                          mov     [rsp+arg_8], rbx
.text:000000014104CFD5 48 89 74 24 18                          mov     [rsp+arg_10], rsi
.text:000000014104CFDA 57                                      push    rdi
.text:000000014104CFDB 48 83 EC 30                             sub     rsp, 30h
.text:000000014104CFDF 49 8B D8                                mov     rbx, r8
.text:000000014104CFE2 48 8B FA                                mov     rdi, rdx
.text:000000014104CFE5 48 8B F1                                mov     rsi, rcx
.text:000000014104CFE8 48 85 C9                                test    rcx, rcx
.text:000000014104CFEB 0F 84 91 00 00 00                       jz      loc_14104D082
.text:000000014104CFF1
.text:000000014104CFF1                         loc_14104CFF1:                          ; DATA XREF: .rdata:000000014290B57C↓o
.text:000000014104CFF1                                                                 ; .rdata:000000014290B58C↓o ...
.text:000000014104CFF1 48 89 6C 24 40                          mov     [rsp+38h+arg_0], rbp
.text:000000014104CFF6 48 8B A9 60 01 00 00                    mov     rbp, [rcx+160h]
.text:000000014104CFFD 48 85 ED                                test    rbp, rbp

48 89 5C 24 10 48 89 74 24 18 57 48 83 EC 30 49 8B D8 48 8B FA 48 8B F1 48 85 C9 ?? ?? ?? ?? ?? ?? 48 89 6C 24 40 48 8B A9 60 01 00 00 48 85 ED