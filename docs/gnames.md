

We want this: TStaticIndirectArrayThreadSafeRead
48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20

00007FF69E40A768 - 00007FF69A460000 = 3FAA768

.text:000000014055E4A0                               ; private: static class TStaticIndirectArrayThreadSafeRead<struct FNameEntry, 4194304, 16384> & FName::GetNames(void)
.text:000000014055E4A0                               ?GetNames@FName@@CAAEAV?$TStaticIndirectArrayThreadSafeRead@UFNameEntry@@$0EAAAAA@$0EAAA@@@XZ proc near
.text:000000014055E4A0                                                                       ; CODE XREF: FCsvStatRegister::GetUniqueIndex(unsigned __int64,int,bool,bool)+F3↑p
.text:000000014055E4A0                                                                       ; FName::InitInternal_FindOrAddNameEntry<char>(char const *,EFindName,ENameCase,ushort,int &)+17E↑p ...
.text:000000014055E4A0
.text:000000014055E4A0                               var_8           = qword ptr -8
.text:000000014055E4A0
.text:000000014055E4A0 48 83 EC 28                                   sub     rsp, 28h
.text:000000014055E4A4 48 8B 05 B5 CB 7A 02                          mov     rax, cs:_qword_GNames
.text:000000014055E4AB 48 85 C0                                      test    rax, rax
.text:000000014055E4AE 75 5F                                         jnz     short loc_14055E50F
.text:000000014055E4B0 B9 08 08 00 00                                mov     ecx, 808h       ; unsigned __int64
.text:000000014055E4B5
.text:000000014055E4B5                               loc_14055E4B5:                          ; DATA XREF: .rdata:000000014288976C↓o
.text:000000014055E4B5                                                                       ; .rdata:0000000142889780↓o ...
.text:000000014055E4B5 48 89 5C 24 20                                mov     [rsp+28h+var_8], rbx
.text:000000014055E4BA E8 61 78 EE FF                                call    ??2FRHICommandList@@SAPEAX_K@Z ; FRHICommandList::operator new(unsigned __int64)
.text:000000014055E4BF 48 8B D8                                      mov     rbx, rax
.text:000000014055E4C2 48 85 C0                                      test    rax, rax
.text:000000014055E4C5 74 38                                         jz      short loc_14055E4FF
.text:000000014055E4C7 C7 80 00 08 00 00 00 00 00 00                 mov     dword ptr [rax+800h], 0


Hook this function? Found by Checking xrefs for TStaticIndirectArrayThreadSafeRead

	/** Singleton to retrieve a table of all names. */
	static TNameEntryArray& GetNames();

.text:000000014055E4A0                         ; private: static class TStaticIndirectArrayThreadSafeRead<struct FNameEntry, 4194304, 16384> & FName::GetNames(void)
.text:000000014055E4A0                         ?GetNames@FName@@CAAEAV?$TStaticIndirectArrayThreadSafeRead@UFNameEntry@@$0EAAAAA@$0EAAA@@@XZ proc near
.text:000000014055E4A0                                                                 ; CODE XREF: FCsvStatRegister::GetUniqueIndex(unsigned __int64,int,bool,bool)+F3↑p
.text:000000014055E4A0                                                                 ; FName::InitInternal_FindOrAddNameEntry<char>(char const *,EFindName,ENameCase,ushort,int &)+17E↑p ...
.text:000000014055E4A0
.text:000000014055E4A0                         var_8           = qword ptr -8
.text:000000014055E4A0
.text:000000014055E4A0 48 83 EC 28                             sub     rsp, 28h
.text:000000014055E4A4 48 8B 05 B5 CB 7A 02                    mov     rax, cs:qword_142D0B060
.text:000000014055E4AB 48 85 C0                                test    rax, rax
.text:000000014055E4AE 75 5F                                   jnz     short loc_14055E50F
.text:000000014055E4B0 B9 08 08 00 00                          mov     ecx, 808h       ; unsigned __int64
.text:000000014055E4B5
.text:000000014055E4B5                         loc_14055E4B5:                          ; DATA XREF: .rdata:000000014288976C↓o
.text:000000014055E4B5                                                                 ; .rdata:0000000142889780↓o ...
.text:000000014055E4B5 48 89 5C 24 20                          mov     [rsp+28h+var_8], rbx
.text:000000014055E4BA E8 61 78 EE FF                          call    ??2FRHICommandList@@SAPEAX_K@Z ; FRHICommandList::operator new(unsigned __int64)
.text:000000014055E4BF 48 8B D8                                mov     rbx, rax
.text:000000014055E4C2 48 85 C0                                test    rax, rax

48 83 EC 28 ?? ?? ?? ?? ?? ?? ?? 48 85 C0 ?? ?? B9 08 08 00 00 48 89 5C 24 20