variable

__int64 __fastcall sub_7FF76B43EF60(__int64 a1, __int64 a2, __int64 a3)
{
  __int64 v3; // rcx

  v3 = qword_7FF76F0492E0;
  if ( !qword_7FF76F0492E0 )
  {
    sub_7FF76BDD6220();
    v3 = qword_7FF76F0492E0;
  }
  qword_7FF76F26ACA8 = (*(__int64 (__fastcall **)(__int64, const wchar_t *, __int64, const wchar_t *, int))(*(_QWORD *)v3 + 8i64))(
                         v3,
                         L"fx.PruneEmittersOnCookByDetailMode",
                         a3,
                         L"Whether to eliminate all emitters that don't match the detail mode.\n"
                          "This will only work if scalability settings affecting detail mode can not be changed at runtim"
                          "e (depends on platform).\n",
                         4);
  off_7FF76F26ACA0 = &unk_7FF76DE79708;
  qword_7FF76F26ACB0 = (*(__int64 (__fastcall **)(__int64))(*(_QWORD *)qword_7FF76F26ACA8 + 64i64))(qword_7FF76F26ACA8);
  return sub_7FF76DD39C2C(sub_7FF76DE3F630);
}


COMMAND

__int64 sub_7FF76B43F360()
{
  _QWORD *v0; // rax
  _QWORD *v1; // rbx
  __int64 v2; // rcx
  __int64 v3; // rax
  _QWORD *v5; // [rsp+30h] [rbp-18h]
  int v6; // [rsp+38h] [rbp-10h]

  v0 = (_QWORD *)sub_7FF76BDF2490(0i64, 32i64, 0i64);
  v5 = v0;
  v1 = v0;
  v6 = 2;
  if ( v0 )
  {
    *v0 = &unk_7FF76DE79FE8;
    v0[1] = sub_7FF76CECA780;
    v0[3] = sub_7FF76BDB4630();
    *v1 = &unk_7FF76DE7A038;
  }
  v2 = qword_7FF76F0492E0;
  if ( !qword_7FF76F0492E0 )
  {
    sub_7FF76BDD6220();
    v2 = qword_7FF76F0492E0;
  }
  
  qword_7FF76F26ACC0 = (*(__int64 (__fastcall **)(__int64, const wchar_t *, const wchar_t *, _QWORD **, _DWORD))(*(_QWORD *)v2 + 128i64))(
                         v2,
                         L"FX.RestartAll",
                         L"Restarts all particle system components",
                         &v5,
                         0);
  off_7FF76F26ACB8 = &unk_7FF76DE79700;
  if ( v6 )
  {
    if ( !v5 )
      return sub_7FF76DD39C2C(sub_7FF76DE3F860);
    (*(void (__fastcall **)(_QWORD *, _QWORD))(*v5 + 48i64))(v5, 0i64);
    v3 = (__int64)v5;
    if ( v5 )
    {
      v3 = sub_7FF76BDF2490(v5, 0i64, 0i64);
      v5 = (_QWORD *)v3;
    }
    v6 = 0;
  }
  else
  {
    v3 = (__int64)v5;
  }
  if ( v3 )
    sub_7FF76BDE5FA0(v3);
  return sub_7FF76DD39C2C(sub_7FF76DE3F860);
}


__int64 sub_7FF76B2EC800()
{
  _QWORD *v0; // rax
  _QWORD *v1; // rbx
  __int64 v2; // rcx
  int v3; // eax
  __int64 v4; // rcx
  _QWORD *v6; // [rsp+38h] [rbp-20h]
  int v7; // [rsp+40h] [rbp-18h]

  v0 = (_QWORD *)sub_7FF76BDF2490(0i64, 32i64, 0i64);
  v1 = v0;
  v6 = v0;
  v7 = 2;
  if ( v0 )
  {
    *v0 = &unk_7FF76DEAF588;
    v0[1] = sub_7FF76B928D70;
    v0[3] = sub_7FF76BDB4630();
    *v1 = &unk_7FF76DEAF5D8;
  }
  v2 = qword_7FF76F0492E0;
  if ( !qword_7FF76F0492E0 )
  {
    sub_7FF76BDD6220();
    v2 = qword_7FF76F0492E0;
  }
  qword_7FF76EFCEED8 = (*(__int64 (__fastcall **)(__int64, const wchar_t *, const wchar_t *, _QWORD **, int))(*(_QWORD *)v2 + 96i64))(
                         v2,
                         L"Dungeons.Level.Seed",
                         L"Prints the current level's seed",
                         &v6,
                         1);
  off_7FF76EFCEED0 = &unk_7FF76DE79700;
  v3 = v7;
  v4 = (__int64)v6;
  if ( v7 && v6 )
  {
    (*(void (__fastcall **)(_QWORD *, _QWORD))(*v6 + 48i64))(v6, 0i64);
    v4 = (__int64)v6;
    if ( v6 )
    {
      v4 = sub_7FF76BDF2490(v6, 0i64, 0i64);
      v6 = (_QWORD *)v4;
    }
    v3 = 0;
    v7 = 0;
  }
  if ( v3 && v4 )
  {
    (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v4 + 48i64))(v4, 0i64);
    v4 = (__int64)v6;
    if ( v6 )
    {
      v4 = sub_7FF76BDF2490(v6, 0i64, 0i64);
      v6 = (_QWORD *)v4;
    }
    v7 = 0;
  }
  if ( v4 )
    sub_7FF76BDE5FA0(v4);
  return sub_7FF76DD39C2C(sub_7FF76DDF50B0);
}

Dungeons.Level.Start

__int64 sub_7FF76B2EEDC0()
{
  _QWORD *v0; // rax
  _QWORD *v1; // rbx
  __int64 v2; // rcx
  int v3; // eax
  __int64 v4; // rcx
  _QWORD *v6; // [rsp+38h] [rbp-20h]
  int v7; // [rsp+40h] [rbp-18h]

  v0 = (_QWORD *)sub_7FF76BDF2490(0i64, 32i64, 0i64);
  v1 = v0;
  v6 = v0;
  v7 = 2;
  if ( v0 )
  {
    *v0 = &unk_7FF76DEAF588;
    v0[1] = sub_7FF76B92F8D0;
    v0[3] = sub_7FF76BDB4630();
    *v1 = &unk_7FF76DEAF5D8;
  }
  v2 = qword_7FF76F0492E0;
  if ( !qword_7FF76F0492E0 )
  {
    sub_7FF76BDD6220();
    v2 = qword_7FF76F0492E0;
  }
  qword_7FF76EFCEEB8 = (*(__int64 (__fastcall **)(__int64, const wchar_t *, const wchar_t *, _QWORD **, int))(*(_QWORD *)v2 + 96i64))(
                         v2,
                         L"Dungeons.Level.Start",
                         L"Start a mission with a given difficulty, threatlevel and an optional seed. (e.g. pumpkinpastures 2 5 1337",
                         &v6,
                         1);
  off_7FF76EFCEEB0 = &unk_7FF76DE79700;
  v3 = v7;
  v4 = (__int64)v6;
  if ( v7 && v6 )
  {
    (*(void (__fastcall **)(_QWORD *, _QWORD))(*v6 + 48i64))(v6, 0i64);
    v4 = (__int64)v6;
    if ( v6 )
    {
      v4 = sub_7FF76BDF2490(v6, 0i64, 0i64);
      v6 = (_QWORD *)v4;
    }
    v3 = 0;
    v7 = 0;
  }
  if ( v3 && v4 )
  {
    (*(void (__fastcall **)(__int64, _QWORD))(*(_QWORD *)v4 + 48i64))(v4, 0i64);
    v4 = (__int64)v6;
    if ( v6 )
    {
      v4 = sub_7FF76BDF2490(v6, 0i64, 0i64);
      v6 = (_QWORD *)v4;
    }
    v7 = 0;
  }
  if ( v4 )
    sub_7FF76BDE5FA0(v4);
  return sub_7FF76DD39C2C(sub_7FF76DDF5A30);
}


DECLARE_DELEGATE_OneParam( FConsoleCommandWithArgsDelegate, const TArray< FString >& );

IConsoleManager::Get().RegisterConsoleCommand(Name, Help, Command, Flags)


enum EConsoleVariableFlags
{
	/**
	 * Default, no flags are set, the value is set by the constructor 
	 */
	ECVF_Default = 0x0,
	/**
	 * Console variables marked with this flag behave differently in a final release build.
	 * Then they are are hidden in the console and cannot be changed by the user.
	 */
	ECVF_Cheat = 0x1,
	/**
	 * Console variables cannot be changed by the user (from console).
	 * Changing from C++ or ini is still possible.
	 */
	ECVF_ReadOnly = 0x4,

00007FF76EFCEE98 should point to a FConsoleCommandXXX (maybe with args?), the one above always points to (__int64)&FAutoConsoleObject::`vftable';
So basically 00007FF76EFCEE90 points to the FAutoConsoleCommand class which has a vftable.
Here's Dungeons.Player.AddEmeralds

________:00007FF76EFCEE90                                                                 ; DATA XREF: sub_7FF76B2EA920+C1↑w
________:00007FF76EFCEE90                                                                 ; sub_7FF76DDF4690+14↑w
________:00007FF76EFCEE98 50 1D 78 57 B7 01 00 00 qword_7FF76EFCEE98 dq 1B757781D50h      ; DATA XREF: sub_7FF76B2EA920+B3↑w
________:00007FF76EFCEE98                                                                 ; sub_7FF76DDF4690+39↑r

00007FF76EFCEE90 - 00007FF76B1D0000 = 3DFEE90

Dungeons.Level.Start 
00007FF76EFCEEB0 - 00007FF76B1D0000 = 0x3DFEEB0


class FConsoleCommandWithArgs : public FConsoleCommandBase
{

public:
	FConsoleCommandWithArgs( const FConsoleCommandWithArgsDelegate& InitDelegate, const TCHAR* InitHelp, const EConsoleVariableFlags InitFlags )
		: FConsoleCommandBase( InitHelp, InitFlags ),
		  Delegate( InitDelegate )
	{
	}

	// interface IConsoleCommand -----------------------------------

	virtual void Release() override
	{
		delete this; 
	} 

	virtual bool Execute( const TArray< FString >& Args, UWorld* InWorld, FOutputDevice& OutputDevice ) override
	{
		return Delegate.ExecuteIfBound( Args );
	}

private:

	/** User function to call when the console command is executed */
	FConsoleCommandWithArgsDelegate Delegate;
};


class FConsoleCommandBase : public IConsoleCommand
{
public:
	/**
	 * Constructor
	 * @param InHelp must not be 0, must not be empty
	 */
	FConsoleCommandBase(const TCHAR* InHelp, EConsoleVariableFlags InFlags)
		: Help(InHelp), Flags(InFlags)
	{
		check(InHelp);
		//check(*Help != 0); for now disabled as there callstack when we crash early during engine init
	}

	// interface IConsoleVariable -----------------------------------

	virtual const TCHAR* GetHelp() const
	{
		return *Help;
	}
	virtual void SetHelp(const TCHAR* InValue)
	{
		check(InValue);
		check(*InValue != 0);

		Help = InValue;
	}
	virtual EConsoleVariableFlags GetFlags() const
	{
		return Flags;
	}
	virtual void SetFlags(const EConsoleVariableFlags Value)
	{
		Flags = Value;
	}

	virtual struct IConsoleCommand* AsCommand()
	{
		return this;
	}

private: // -----------------------------------------

	// not using TCHAR* to allow chars support reloading of modules (otherwise we would keep a pointer into the module)
	FString Help;

	EConsoleVariableFlags Flags;
};



.text:0000000140462960                         ; public: virtual void FConsoleManager::ForEachConsoleObjectThatContains(class TBaseDelegate<void, wchar_t const *, class IConsoleObject *> const &, wchar_t const *)const
.text:0000000140462960                         ?ForEachConsoleObjectThatContains@FConsoleManager@@UEBAXAEBV?$TBaseDelegate@XPEB_WPEAVIConsoleObject@@@@PEB_W@Z proc near
.text:0000000140462960                                                                 ; DATA XREF: .rdata:00000001420F1598↓o
.text:0000000140462960                                                                 ; .rdata:000000014287A404↓o ...
.text:0000000140462960
.text:0000000140462960                         var_90          = qword ptr -90h
.text:0000000140462960                         var_88          = qword ptr -88h
.text:0000000140462960                         Dst             = qword ptr -80h
.text:0000000140462960                         var_70          = xmmword ptr -70h
.text:0000000140462960                         var_60          = qword ptr -60h
.text:0000000140462960                         var_58          = xmmword ptr -58h
.text:0000000140462960                         anonymous_0     = byte ptr -48h
.text:0000000140462960                         var_30          = qword ptr -30h
.text:0000000140462960                         var_28          = qword ptr -28h
.text:0000000140462960                         var_20          = qword ptr -20h
.text:0000000140462960                         var_18          = qword ptr -18h
.text:0000000140462960                         var_10          = qword ptr -10h
.text:0000000140462960                         arg_0           = qword ptr  10h
.text:0000000140462960                         arg_8           = qword ptr  18h
.text:0000000140462960                         arg_10          = qword ptr  20h
.text:0000000140462960                         arg_18          = qword ptr  28h
.text:0000000140462960
.text:0000000140462960 48 8B C4                                mov     rax, rsp
.text:0000000140462963 4C 89 40 18                             mov     [rax+18h], r8
.text:0000000140462967 48 89 50 10                             mov     [rax+10h], rdx
.text:000000014046296B 55                                      push    rbp
.text:000000014046296C 53                                      push    rbx
.text:000000014046296D 48 8D 68 A1                             lea     rbp, [rax-5Fh]
.text:0000000140462971 48 81 EC A8 00 00 00                    sub     rsp, 0A8h
.text:0000000140462978
.text:0000000140462978                         loc_140462978:                          ; DATA XREF: .rdata:000000014287A404↓o
.text:0000000140462978                                                                 ; .rdata:000000014287A41C↓o ...
.text:0000000140462978 48 89 70 20                             mov     [rax+20h], rsi
.text:000000014046297C 49 8B F0                                mov     rsi, r8
.text:000000014046297F 48 89 78 E8                             mov     [rax-18h], rdi
.text:0000000140462983 48 8B F9                                mov     rdi, rcx
.text:0000000140462986 33 C9                                   xor     ecx, ecx
.text:0000000140462988 4C 89 60 E0                             mov     [rax-20h], r12
.text:000000014046298C 4C 89 78 C8                             mov     [rax-38h], r15
.text:0000000140462990 4C 8B E2                                mov     r12, rdx


48 8B C4 4C 89 40 18 48 89 50 10 55 53 48 8D 68 A1 48 81 EC A8 00 00 00 48 89 70 20 49 8B F0

void __fastcall UConsole::ConsoleCommand(UConsole *this, const struct FString *a2)
this calls in to a few Exec() in 

else if( GEngine->Exec( InWorld, Cmd,Ar) )
  UnrealEngine.cpp
        
    bool UEngine::Exec( UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar )
    {

      	else if(IConsoleManager::Get().ProcessUserConsoleInput(Cmd, Ar, InWorld))
        {
          // console variable interaction (get value, set value or get help)
          return true;
        }

      SO if we hook ProcessUserConsoleInput and run a console command that's not caught by other things
      eventually it should reach ProcessUserConsoleInput


.text:0000000140469070                         ; bool FConsoleManager::ProcessUserConsoleInput(FConsoleManager *__hidden this, const wchar_t *, struct FOutputDevice *, struct UWorld *)
.text:0000000140469070                         ?ProcessUserConsoleInput@FConsoleManager@@UEAA_NPEB_WAEAVFOutputDevice@@PEAVUWorld@@@Z proc near
.text:0000000140469070                                                                 ; DATA XREF: .rdata:00000001420F15A0↓o
.text:0000000140469070                                                                 ; .rdata:000000014287A478↓o ...

...

.text:0000000140469070
.text:0000000140469070 48 8B C4                                mov     rax, rsp
.text:0000000140469073 4C 89 48 20                             mov     [rax+20h], r9
.text:0000000140469077 4C 89 40 18                             mov     [rax+18h], r8
.text:000000014046907B 48 89 48 08                             mov     [rax+8], rcx
.text:000000014046907F 55                                      push    rbp
.text:0000000140469080 56                                      push    rsi
.text:0000000140469081 48 8D 68 A1                             lea     rbp, [rax-5Fh]
.text:0000000140469085 48 81 EC B8 00 00 00                    sub     rsp, 0B8h
.text:000000014046908C 33 F6                                   xor     esi, esi
.text:000000014046908E
.text:000000014046908E                         loc_14046908E:                          ; DATA XREF: .rdata:000000014287A478↓o
.text:000000014046908E                                                                 ; .rdata:000000014287A488↓o ...
.text:000000014046908E 48 89 58 E8                             mov     [rax-18h], rbx
.text:0000000140469092 48 8B DA                                mov     rbx, rdx
.text:0000000140469095 48 89 78 E0                             mov     [rax-20h], rdi

48 8B C4 4C 89 48 20 4C 89 40 18 48 89 48 08 55 56 48 8D 68 A1 48 81 EC B8 00 00 00 33 F6
00007FF76BDCFAF0 - 00007FF76B1D0000 = 0xBFFAF0


Console.cpp
		// If there are any players, execute the command in the first local player's context.
		APlayerController* PC = GameInstance->GetFirstLocalPlayerController();
		PC->ConsoleCommand(Command);

    which probably leads to UPlayer

    FString UPlayer::ConsoleCommand(const FString& Cmd, bool bWriteToLog) {

      resulting in:
      if (!Exec(GetWorld(), Line, EffectiveOutputDevice))
      which calls on UObject (which belongs to the player or other things)
      	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
	{
		return CallFunctionByNameWithArguments(Cmd, Ar, Executor);
	}


  ScriptCore.cpp
    
  bool UObject::CallFunctionByNameWithArguments(const TCHAR* Str, FOutputDevice& Ar, UObject* Executor, bool bForceCallWithNonExec/*=false*/)
  {

    well that just led to the code on how to call a UFunction using ProcessEvent

Tmap is going to be hellish to re-create. Maybe try TBaseDelegate instead
public: virtual void FConsoleManager::ForEachConsoleObjectThatContains(class TBaseDelegate<void, wchar_t const *, class IConsoleObject *> const &, wchar_t const *)const

