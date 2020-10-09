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

00007FF76EFCEE98 should point to a FAutoConsoleCommand, the one above always points to (__int64)&FAutoConsoleObject::`vftable';

________:00007FF76EFCEE90                                                                 ; DATA XREF: sub_7FF76B2EA920+C1↑w
________:00007FF76EFCEE90                                                                 ; sub_7FF76DDF4690+14↑w
________:00007FF76EFCEE98 50 1D 78 57 B7 01 00 00 qword_7FF76EFCEE98 dq 1B757781D50h      ; DATA XREF: sub_7FF76B2EA920+B3↑w
________:00007FF76EFCEE98                                                                 ; sub_7FF76DDF4690+39↑r