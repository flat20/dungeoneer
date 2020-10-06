000140224AA4 48 89 7C 24 50                                mov     [rsp+290h+var_240], rdi
.text:0000000140224AA9 E8 72 7B 48 00                                call    ?GetTransientPackage@@YAPEAVUPackage@@XZ ; GetTransientPackage(void)
.text:0000000140224AAE 48 89 7C 24 30                                mov     [rsp+290h+var_260], rdi
.text:0000000140224AB3 48 8B C8                                      mov     rcx, rax
.text:0000000140224AB6 40 88 7C 24 28                                mov     byte ptr [rsp+290h+var_268], dil
.text:0000000140224ABB 45 33 C9                                      xor     r9d, r9d
.text:0000000140224ABE 4C 8B C7                                      mov     r8, rdi
.text:0000000140224AC1 48 89 7C 24 20                                mov     [rsp+290h+var_270], rdi
.text:0000000140224AC6 48 8B D3                                      mov     rdx, rbx
.text:0000000140224AC9 E8 12 21 00 00                                call    ??$NewObject@VUUserWidget@@@@YAPEAVUUserWidget@@PEAVUObject@@PEAVUClass@@VFName@@W4EObjectFlags@@0_NPEAUFObjectInstancingGraph@@@Z ; #STR: "NewObject with empty name can't be used to create default
.text:0000000140224ACE 48 8B 4C 24 40                                mov     rcx, [rsp+290h+var_250] ; void *
.text:0000000140224AD3 48 89 05 6E 69 BE 02                          mov     cs:?GEngine@@3PEAVUEngine@@EA, rax ; UEngine * GEngine
.text:0000000140224ADA 48 85 C9                                      test    rcx, rcx
.text:0000000140224ADD 74 05                                         jz      short loc_140224AE4
.text:0000000140224ADF E8 DC AF 25 00                                call    ?Free@FMemory@@SAXPEAX@Z ; FMemory::Free(void *)

48 89 7C 24 30 48 8B C8 40 88 7C 24 28 45 33 C9 4C 8B C7 48 89 7C 24 20 48 8B D3 ?? ?? ?? ?? ?? 48 8B 4C 24 40

00007FF69E50AA68 - 00007FF69A460000 = 40AAA68
00007FF69E50AA68 - 00007FF69A460000 = 40AAA68
Trying to find GameViewPort in UEngine. The property above it is IEngineLoop* EngineLoop;
UEngine::Init(IEngineLoop *) sets it using:

mov     [rcx+748h], rdx

So offset for class UGameViewportClient* GameViewport should be:

0x750