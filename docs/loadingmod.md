.text:000000014054D780                         ; public: class IModuleInterface * FModuleManager::LoadModule(class FName)
.text:000000014054D780                         ?LoadModule@FModuleManager@@QEAAPEAVIModuleInterface@@VFName@@@Z proc near
.text:000000014054D780                                                                 ; CODE XREF: FEngineLoop::Init(void)+38C↑p
.text:000000014054D780                                                                 ; FEngineLoop::Init(void)+564↑p ...
.text:000000014054D780
.text:000000014054D780                         arg_0           = qword ptr  8
.text:000000014054D780                         arg_10          = byte ptr  18h
.text:000000014054D780
.text:000000014054D780 48 89 5C 24 08                          mov     [rsp+arg_0], rbx
.text:000000014054D785 57                                      push    rdi
.text:000000014054D786 48 83 EC 20                             sub     rsp, 20h
.text:000000014054D78A 80 3D 6F B5 6B 02 00                    cmp     cs:?GIsGameThreadIdInitialized@@3_NA, 0 ; bool GIsGameThreadIdInitialized
.text:000000014054D791 48 8B DA                                mov     rbx, rdx
.text:000000014054D794 48 8B F9                                mov     rdi, rcx
.text:000000014054D797 74 06                                   jz      short loc_14054D79F
.text:000000014054D799 FF 15 21 00 B0 01                       call    cs:__imp_GetCurrentThreadId
.text:000000014054D79F
.text:000000014054D79F                         loc_14054D79F:                          ; CODE XREF: FModuleManager::LoadModule(FName)+17↑j
.text:000000014054D79F 4C 8D 44 24 40                          lea     r8, [rsp+28h+arg_10]
.text:000000014054D7A4 48 8B D3                                mov     rdx, rbx
.text:000000014054D7A7 48 8B CF                                mov     rcx, rdi
.text:000000014054D7AA E8 11 00 00 00                          call    ?LoadModuleWithFailureReason@FModuleManager@@QEAAPEAVIModuleInterface@@VFName@@AEAW4EModuleLoadResult@@@Z ; FModuleManager::LoadModuleWithFailureReason(FName,EModuleLoadResult &)
.text:000000014054D7AF 48 8B 5C 24 30                          mov     rbx, [rsp+28h+arg_0]
.text:000000014054D7B4 48 83 C4 20                             add     rsp, 20h
.text:000000014054D7B8 5F                                      pop     rdi
.text:000000014054D7B9 C3                                      retn

48 89 5C 24 08 57 48 83 EC 20 ?? ?? ?? ?? ?? ?? ?? 48 8B DA 48 8B F9 ?? ?? ?? ?? ?? ?? ?? ?? 4C 8D 44 24 40 48 8B D3 48 8B CF
00007FF76BEB1FB0 - 00007FF76B1D0000 = CE1FB0

.text:000000014054B140                               ; struct FModuleManager *FModuleManager::Get(void)
.text:000000014054B140                               ?Get@FModuleManager@@SAAEAV1@XZ proc near
.text:000000014054B140                                                                       ; CODE XREF: sub_1400FA3B0+7A↑p
.text:000000014054B140                                                                       ; sub_1400FA7A0+7A↑p ...
.text:000000014054B140
.text:000000014054B140                               var_8           = qword ptr -8
.text:000000014054B140                               arg_0           = qword ptr  8
.text:000000014054B140
.text:000000014054B140 48 83 EC 28                                   sub     rsp, 28h
.text:000000014054B144 48 8B 05 5D FA 6B 02                          mov     rax, cs:qword_142C0ABA8
.text:000000014054B14B 48 85 C0                                      test    rax, rax
.text:000000014054B14E 0F 85 EE 01 00 00                             jnz     loc_14054B342
.text:000000014054B154 65 48 8B 04 25 58 00 00 00                    mov     rax, gs:58h
.text:000000014054B15D 8B 0D 7D 1D 90 02                             mov     ecx, cs:_tls_index
.text:000000014054B163 41 B8 18 00 00 00                             mov     r8d, 18h
.text:000000014054B169 48 8B 14 C8                                   mov     rdx, [rax+rcx*8]
.text:000000014054B16D 41 8B 04 10                                   mov     eax, [r8+rdx]
.text:000000014054B171 39 05 61 FA 6B 02                             cmp     cs:dword_142C0ABD8, eax
.text:000000014054B177 0F 8F CA 01 00 00                             jg      loc_14054B347
.text:000000014054B17D
.text:000000014054B17D                               loc_14054B17D:                          ; CODE XREF: FModuleManager::Get(void)+21A↓j
.text:000000014054B17D                                                                       ; FModuleManager::Get(void)+257↓j
.text:000000014054B17D 48 8D 0D 2C FA 6B 02                          lea     rcx, stru_142C0ABB0 ; lpCriticalSection
.text:000000014054B184 FF 15 5E 26 B0 01                             call    cs:__imp_TryEnterCriticalSection
.text:000000014054B18A 85 C0                                         test    eax, eax
.text:000000014054B18C 75 0D                                         jnz     short loc_14054B19B
.text:000000014054B18E 48 8D 0D 1B FA 6B 02                          lea     rcx, stru_142C0ABB0 ; lpCriticalSection
.text:000000014054B195 FF 15 45 26 B0 01                             call    cs:__imp_EnterCriticalSection
.text:000000014054B19B
.text:000000014054B19B                               loc_14054B19B:                          ; CODE XREF: FModuleManager::Get(void)+4C↑j
.text:000000014054B19B 48 83 3D 05 FA 6B 02 00                       cmp     cs:qword_142C0ABA8, 0
.text:000000014054B1A3 0F 85 85 01 00 00                             jnz     loc_14054B32E
.text:000000014054B1A9 80 3D 50 DB 6B 02 00                          cmp     cs:?GIsGameThreadIdInitialized@@3_NA, 0 ; bool GIsGameThreadIdInitialized
.text:000000014054B1B0
.text:000000014054B1B0                               loc_14054B1B0:                          ; DATA XREF: .rdata:0000000142887CBC↓o
.text:000000014054B1B0                                                                       ; .rdata:0000000142887CD0↓o ...
.text:000000014054B1B0 48 89 7C 24 20                                mov     [rsp+28h+var_8], rdi
.text:000000014054B1B5 74 06                                         jz      short loc_14054B1BD
.text:000000014054B1B7 FF 15 03 26 B0 01                             call    cs:__imp_GetCurrentThreadId

48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? ?? ?? ?? ?? 65 48 8B 04 25 58 00 00 00 8B 0D ?? ?? ?? ?? 41 B8 ?? ?? ?? ?? 48 8B 14 C8 41 8B 04 10 39 05 ?? ?? ?? ?? ?? ?? ?? ?? ?? ?? 48 8D

00007FF76BEAF970 - 00007FF76B1D0000 = CDF970 Hook with CE and see how far we get

FString FileName = FModuleManifest::GetFileName(FPlatformProcess::GetModulesDirectory(), false);
const FString FGenericPlatformProcess::GetModulesDirectory()
{
	return FPaths::Combine(*FPaths::EngineDir(), TEXT("Binaries"), FPlatformProcess::GetBinariesSubdirectory());
}

const TCHAR* FGenericPlatformProcess::GetBinariesSubdirectory()
{
	return TEXT("");
}


.text:0000000140558500                               ; public: FName::FName(wchar_t const *, enum  EFindName)
.text:0000000140558500                               ??0FName@@QEAA@PEB_WW4EFindName@@@Z proc near
.text:0000000140558500                                                                       ; CODE XREF: sub_1400FA4C0+14↑j
.text:0000000140558500                                                                       ; sub_1400FA5F0+14↑j ...
.text:0000000140558500
.text:0000000140558500                               var_18          = byte ptr -18h
.text:0000000140558500                               var_10          = dword ptr -10h
.text:0000000140558500                               arg_0           = qword ptr  8
.text:0000000140558500
.text:0000000140558500 40 53                                         push    rbx
.text:0000000140558502 48 83 EC 30                                   sub     rsp, 30h
.text:0000000140558506 48 8B D9                                      mov     rbx, rcx
.text:0000000140558509 48 85 D2                                      test    rdx, rdx
.text:000000014055850C 74 21                                         jz      short loc_14055852F
.text:000000014055850E 45 8B C8                                      mov     r9d, r8d
.text:0000000140558511 C7 44 24 28 FF FF FF FF                       mov     [rsp+38h+var_10], 0FFFFFFFFh
.text:0000000140558519 45 33 C0                                      xor     r8d, r8d
.text:000000014055851C C6 44 24 20 01                                mov     [rsp+38h+var_18], 1
.text:0000000140558521 E8 9A A4 00 00                                call    ?Init@FName@@AEAAXPEB_WHW4EFindName@@_NH@Z ; FName::Init(wchar_t const *,int,EFindName,bool,int)
.text:0000000140558526 48 8B C3                                      mov     rax, rbx
.text:0000000140558529 48 83 C4 30                                   add     rsp, 30h
.text:000000014055852D 5B                                            pop     rbx
.text:000000014055852E C3                                            retn
.text:000000014055852F                               ; ---------------------------------------------------------------------------
.text:000000014055852F
.text:000000014055852F                               loc_14055852F:                          ; CODE XREF: FName::FName(wchar_t const *,EFindName)+C↑j
.text:000000014055852F 33 C0                                         xor     eax, eax
.text:0000000140558531 48 89 44 24 40                                mov     [rsp+38h+arg_0], rax
.text:0000000140558536 48 89 01                                      mov     [rcx], rax
.text:0000000140558539 48 8B C3                                      mov     rax, rbx
.text:000000014055853C 48 83 C4 30                                   add     rsp, 30h
.text:0000000140558540 5B                                            pop     rbx
.text:0000000140558541 C3                                            retn

40 53 48 83 EC 30 48 8B D9 48 85 D2 ?? ?? 45 8B C8 C7 44 24 28 FF FF FF FF 45 33 C0 C6 44 24 20 01 ?? ?? ?? ?? ?? 48 8B C3 48 83 C4 30 5B C3 33 C0 48 89 44 24 40 48 89 01 48 8B C3 48 83 C4 30 5B C3

first result takes an FName as its first param. and then a const char. Seems to call Init anyway.

void FName::Init(const WIDECHAR* InName, int32 InNumber, EFindName FindType, bool bSplitName, int32 HardcodeIndex)
.text:00000001405629C0                               ; void __stdcall __high FName::Init(const wchar_t *, int, enum EFindName, bool, int)
.text:00000001405629C0                               ?Init@FName@@AEAAXPEB_WHW4EFindName@@_NH@Z proc near
.text:00000001405629C0                                                                       ; CODE XREF: sub_140115500+32↑p
.text:00000001405629C0                                                                       ; sub_140115570+32↑p ...
.text:00000001405629C0
.text:00000001405629C0                               var_858         = dword ptr -858h
.text:00000001405629C0                               var_850         = dword ptr -850h
.text:00000001405629C0                               var_848         = word ptr -848h
.text:00000001405629C0                               var_838         = dword ptr -838h
.text:00000001405629C0                               Dest            = word ptr -828h
.text:00000001405629C0                               var_7A8         = qword ptr -7A8h
.text:00000001405629C0                               var_7A0         = qword ptr -7A0h
.text:00000001405629C0                               var_28          = qword ptr -28h
.text:00000001405629C0                               arg_10          = qword ptr  18h
.text:00000001405629C0                               arg_20          = byte ptr  28h
.text:00000001405629C0                               arg_28          = dword ptr  30h
.text:00000001405629C0
.text:00000001405629C0                               ; __unwind { // __GSHandlerCheck
.text:00000001405629C0 48 89 5C 24 18                                mov     [rsp+arg_10], rbx
.text:00000001405629C5 55                                            push    rbp
.text:00000001405629C6 56                                            push    rsi
.text:00000001405629C7 57                                            push    rdi
.text:00000001405629C8 48 81 EC 60 08 00 00                          sub     rsp, 860h
.text:00000001405629CF 48 8B 05 02 EA 65 02                          mov     rax, cs:__security_cookie
.text:00000001405629D6 48 33 C4                                      xor     rax, rsp
.text:00000001405629D9 48 89 84 24 50 08 00 00                       mov     [rsp+878h+var_28], rax
.text:00000001405629E1 0F B7 02                                      movzx   eax, word ptr [rdx]
.text:00000001405629E4 48 8B E9                                      mov     rbp, rcx
.text:00000001405629E7 41 8B F1                                      mov     esi, r9d
.text:00000001405629EA 41 8B F8                                      mov     edi, r8d
.text:00000001405629ED 48 8B DA                                      mov     rbx, rdx
.text:00000001405629F0 48 8B CA                                      mov     rcx, rdx
.text:00000001405629F3 66 85 C0                                      test    ax, ax

48 89 5C 24 18 55 56 57 48 81 EC 60 08 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 84 24 50 08 00 00 0F B7 02

__int64 __fastcall FModuleManager::LoadModuleWithFailureReason(__int64 a1, __int64 a2, _DWORD *a3)
.text:000000014054D7C0
.text:000000014054D7C0                               ; public: class IModuleInterface * FModuleManager::LoadModuleWithFailureReason(class FName, enum  EModuleLoadResult &)
.text:000000014054D7C0                               ?LoadModuleWithFailureReason@FModuleManager@@QEAAPEAVIModuleInterface@@VFName@@AEAW4EModuleLoadResult@@@Z proc near
.text:000000014054D7C0                                                                       ; CODE XREF: FModuleManager::LoadModule(FName)+2A↑p
.text:000000014054D7C0                                                                       ; FModuleDescriptor::LoadModulesForPhase(ELoadingPhase::Type,TArray<FModuleDescriptor,FDefaultAllocator> const &,TMap<FName,EModuleLoadResult,FDefaultSetAllocator,TDefaultMapHashableKeyFuncs<FName,EModuleLoadResult,0>> &)+167↓p
.text:000000014054D7C0                                                                       ; DATA XREF: ...
.text:000000014054D7C0
.text:000000014054D7C0                               var_C0          = qword ptr -0C0h
.text:000000014054D7C0                               var_B8          = qword ptr -0B8h
.text:000000014054D7C0                               var_B0          = dword ptr -0B0h
.text:000000014054D7C0                               var_A8          = xmmword ptr -0A8h
.text:000000014054D7C0                               var_98          = qword ptr -98h
.text:000000014054D7C0                               var_90          = qword ptr -90h
.text:000000014054D7C0                               var_88          = byte ptr -88h
.text:000000014054D7C0                               var_80          = qword ptr -80h
.text:000000014054D7C0                               var_78          = byte ptr -78h
.text:000000014054D7C0                               var_70          = qword ptr -70h
.text:000000014054D7C0                               var_68          = byte ptr -68h
.text:000000014054D7C0                               var_50          = xmmword ptr -50h
.text:000000014054D7C0                               var_40          = byte ptr -40h
.text:000000014054D7C0                               var_38          = qword ptr -38h
.text:000000014054D7C0                               arg_8           = qword ptr  18h
.text:000000014054D7C0                               arg_18          = qword ptr  28h
.text:000000014054D7C0
.text:000000014054D7C0                               ; __unwind { // __GSHandlerCheck
.text:000000014054D7C0 48 89 54 24 10                                mov     [rsp-8+arg_8], rdx
.text:000000014054D7C5 55                                            push    rbp
.text:000000014054D7C6 53                                            push    rbx
.text:000000014054D7C7 56                                            push    rsi
.text:000000014054D7C8 57                                            push    rdi
.text:000000014054D7C9 41 54                                         push    r12
.text:000000014054D7CB 41 55                                         push    r13
.text:000000014054D7CD 41 56                                         push    r14
.text:000000014054D7CF 48 8D 6C 24 D9                                lea     rbp, [rsp-27h]
.text:000000014054D7D4 48 81 EC B0 00 00 00                          sub     rsp, 0B0h
.text:000000014054D7DB 48 8B 05 F6 3B 67 02                          mov     rax, cs:__security_cookie
.text:000000014054D7E2 48 33 C4                                      xor     rax, rsp
.text:000000014054D7E5 48 89 45 1F                                   mov     [rbp+57h+var_38], rax
.text:000000014054D7E9 33 FF                                         xor     edi, edi
.text:000000014054D7EB 4D 8B E0                                      mov     r12, r8
.text:000000014054D7EE 41 89 38                                      mov     [r8], edi
.text:000000014054D7F1 4C 8B E9                                      mov     r13, rcx
.text:000000014054D7F4 4C 8B C2                                      mov     r8, rdx
.text:000000014054D7F7 44 8B F7                                      mov     r14d, edi
.text:000000014054D7FA 48 8D 55 97                                   lea     rdx, [rbp+57h+var_C0]

48 89 54 24 10 55 53 56 57 41 54 41 55 41 56 48 8D 6C 24 D9 48 81 EC B0 00 00 00

The code to load a dll dynamically isn't compiled in anyway. IS_MONOLITHIC..
So would need to pretend to be statically linked or re-implement the code to load it dynamically?