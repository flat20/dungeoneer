1. Find reference to Actor class. (UClass)
2. Then StaticLoadObject(actorClass, NULL, "/Dungeons/Content/Cues/BP_MyTest.BP_MyTest")
3. Add To Root? Will that "beginplay" on it?
	"This event is triggered for all Actors when the game is started, any Actors spawned after the game is started will have this called immediately."
There's an event Level Start which might be better to use? I could listen for all BeginPlay events and see if my object receives one.

UClass* MyItemBlueprintClass = StaticLoadClass(UObject::StaticClass(), NULL, TEXT("/Dungeons/Content/Cues/BP_MyTest.BP_MyTest"), NULL, LOAD_None, NULL);
 FActorSpawnParameters SpawnInfo;
 SpawnInfo.Owner = this;
 SpawnInfo.Instigator = Instigator;
 ApsItemActor* obj = spawnManager->currentWorld->SpawnActor<ApsItemActor>(MyItemBlueprintClass, newlocation, GetActorRotation(), SpawnInfo);


How about package = LoadPackage(nullptr, TEXT("/MyMountPoint/Datas/CustomAsset"), LOAD_None);
https://answers.unrealengine.com/questions/500286/view.html

https://answers.unrealengine.com/questions/348513/how-to-load-assets-from-a-pak-file-at-runtime.html
Some depcrecated stuff there.

For example, a path of Content/Characters/MyCharacter would save to /UE4/MyProject/Content/Characters/MyCharacter.MyCharacter.uasset. 

So we can pass in NULL to LoadObject
LoadObject<T>(NULL, *PathName);

ConstructorHelpers.h

template overrides?

	template<>
	inline UPackage* FindOrLoadObject<UPackage>( FString& PathName )

namespace ConstructorHelpersInternal
{
	template<typename T>
	inline T* FindOrLoadObject( FString& PathName )
	{
		// If there is no dot, add a dot and repeat the object name.
		int32 PackageDelimPos = INDEX_NONE;
		PathName.FindChar( TCHAR('.'), PackageDelimPos );
		if( PackageDelimPos == INDEX_NONE )
		{
			int32 ObjectNameStart = INDEX_NONE;
			PathName.FindLastChar( TCHAR('/'), ObjectNameStart );
			if( ObjectNameStart != INDEX_NONE )
			{
				const FString ObjectName = PathName.Mid( ObjectNameStart+1 );
				PathName += TCHAR('.');
				PathName += ObjectName;
			}
		}

		UClass* Class = T::StaticClass();
		Class->GetDefaultObject(); // force the CDO to be created if it hasn't already
		T* ObjectPtr = LoadObject<T>(NULL, *PathName);
		if (ObjectPtr)
		{
			ObjectPtr->AddToRoot();
		}
		return ObjectPtr;
	}

Here's the one for UClass, others look similar, perhaps difference at the end?

.text:0000000141822AF0                         ; class UClass * ConstructorHelpersInternal::FindOrLoadObject<class UClass>(class FString &)
.text:0000000141822AF0                         ??$FindOrLoadObject@VUClass@@@ConstructorHelpersInternal@@YAPEAVUClass@@AEAVFString@@@Z proc near
.text:0000000141822AF0                                                                 ; CODE XREF: AWorldSettings::AWorldSettings(FObjectInitializer const &)+3FD↓p
.text:0000000141822AF0 40 56                                   push    rsi
.text:0000000141822AF2 48 83 EC 60                             sub     rsp, 60h
.text:0000000141822AF6 4C 8B 01                                mov     r8, [rcx]
.text:0000000141822AF9 33 F6                                   xor     esi, esi
.text:0000000141822AFB 4C 63 49 08                             movsxd  r9, dword ptr [rcx+8]
.text:0000000141822AFF 49 8B D0                                mov     rdx, r8
.text:0000000141822B02 4C 89 A4 24 88 00 00 00                 mov     [rsp+88h], r12
.text:0000000141822B0A 4C 8D 25 03 AE 84 00                    lea     r12, word_14206D914
.text:0000000141822B11 4C 89 74 24 58                          mov     [rsp+58h], r14
.text:0000000141822B16 4C 8B F1                                mov     r14, rcx
.text:0000000141822B19 4B 8D 04 48                             lea     rax, [r8+r9*2]
.text:0000000141822B1D 49 3B C0                                cmp     rax, r8
.text:0000000141822B20 0F 84 CB 01 00 00                       jz

40 56 48 83 EC 60 4C 8B 01 33 F6 4C 63 49 08 49 8B D0 4C 89 A4 24 88 00 00 00

/**
 * Find or load an object by string name with optional outer and filename specifications.
 * These are optional because the InName can contain all of the necessary information.
 *
 * @param ObjectClass	The class (or a superclass) of the object to be loaded.
 * @param InOuter		An optional object to narrow where to find/load the object from
 * @param Name			String name of the object. If it's not fully qualified, InOuter and/or Filename will be needed
 * @param Filename		An optional file to load from (or find in the file's package object)
 * @param LoadFlags		Flags controlling how to handle loading from disk, from the ELoadFlags enum
 * @param Sandbox		A list of packages to restrict the search for the object
 * @param bAllowObjectReconciliation	Whether to allow the object to be found via FindObject in the case of seek free loading
 * @param InSerializeContext	Additional context when called during serialization
 *
 * @return The object that was loaded or found. nullptr for a failure.
 */
COREUOBJECT_API UObject* StaticLoadObject( UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr, bool bAllowObjectReconciliation = true, FUObjectSerializeContext* InSerializeContext = nullptr );

/** Version of StaticLoadObject() that will load classes */
COREUOBJECT_API UClass* StaticLoadClass(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr);


StaticLoadClass needs a BaseClass so maybe we need to provide something like Actor (Class), that's from object.txt.

These are the same:
https://answers.unrealengine.com/questions/476579/view.html
UMaterial* mt1 = LoadObject<UMaterial>(nullptr, TEXT("/Game/Map/Materials/grass.grass"));
 UMaterial* mt2 = (UMaterial*)StaticLoadObject( T::StaticClass(), nullptr, TEXT("/Game/Map/Materials/grass.grass"));

.text:00000001406E9FA0                         ; class UObject * StaticLoadObject(class UClass *, class UObject *, wchar_t const *, wchar_t const *, unsigned int, class UPackageMap *, bool, struct FUObjectSerializeContext *)
.text:00000001406E9FA0                         ?StaticLoadObject@@YAPEAVUObject@@PEAVUClass@@PEAV1@PEB_W2IPEAVUPackageMap@@_NPEAUFUObjectSerializeContext@@@Z proc near
.text:00000001406E9FA0 40 55                                   push    rbp
.text:00000001406E9FA2 53                                      push    rbx
.text:00000001406E9FA3 56                                      push    rsi
.text:00000001406E9FA4 57                                      push    rdi
.text:00000001406E9FA5 41 54                                   push    r12
.text:00000001406E9FA7 41 55                                   push    r13
.text:00000001406E9FA9 41 56                                   push    r14
.text:00000001406E9FAB 41 57                                   push    r15
.text:00000001406E9FAD 48 8D AC 24 18 FE FF FF                 lea     rbp, [rsp-1E8h]
.text:00000001406E9FB5 48 81 EC E8 02 00 00                    sub     rsp, 2E8h
.text:00000001406E9FBC 48 8B 05 15 74 4D 02                    mov     rax, cs:__security_cookie
.text:00000001406E9FC3 48 33 C4                                xor     rax, rsp
.text:00000001406E9FC6 48 89 85 D0 01 00 00                    mov     [rbp+220h+var_50], rax
.text:00000001406E9FCD 48 8B 85 68 02 00 00                    mov     rax, [rbp+220h+arg_38]
.text:00000001406E9FD4 33 F6                                   xor     esi, esi

40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 18 FE FF FF 48 81 EC E8 02 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 D0 01 00 00 48 8B 85 68 02 00 00

00007FF69B2D98C0 - 00007FF69A460000 = E798C0

.text:00000001406E9AF0
.text:00000001406E9AF0                         ; class UClass * StaticLoadClass(class UClass *, class UObject *, wchar_t const *, wchar_t const *, unsigned int, class UPackageMap *)
.text:00000001406E9AF0                         ?StaticLoadClass@@YAPEAVUClass@@PEAV1@PEAVUObject@@PEB_W2IPEAVUPackageMap@@@Z proc near
.text:00000001406E9AF0                                                                 ; CODE XREF: FEngineLoop::Init(void)+143↑p
.text:00000001406E9AF0                                                                 ; FEngineLoop::PreInit(wchar_t const *)+3253↑p ...
.text:00000001406E9AF0

.text:00000001406E9AF0 40 55                                   push    rbp
.text:00000001406E9AF2 53                                      push    rbx
.text:00000001406E9AF3 56                                      push    rsi
.text:00000001406E9AF4 57                                      push    rdi
.text:00000001406E9AF5 41 54                                   push    r12
.text:00000001406E9AF7 41 55                                   push    r13
.text:00000001406E9AF9 41 56                                   push    r14
.text:00000001406E9AFB 41 57                                   push    r15
.text:00000001406E9AFD 48 8D AC 24 08 FF FF FF                 lea     rbp, [rsp-0F8h]
.text:00000001406E9B05 48 81 EC F8 01 00 00                    sub     rsp, 1F8h
.text:00000001406E9B0C 48 8B 05 C5 78 4D 02                    mov     rax, cs:__security_cookie
.text:00000001406E9B13 48 33 C4                                xor     rax, rsp
.text:00000001406E9B16 48 89 85 E0 00 00 00                    mov     [rbp+130h+var_50], rax
.text:00000001406E9B1D 8B BD 60 01 00 00                       mov     edi, [rbp+130h+arg_20]
.text:00000001406E9B23 4D 8B F9                                mov     r15, r9
.text:00000001406E9B26 48 8B 9D 68 01 00 00                    mov     rbx, [rbp+130h+arg_28]
.text:00000001406E9B2D 4D 8B F0                                mov     r14, r8
.text:00000001406E9B30 48 8B F2                                mov     rsi, rdx
.text:00000001406E9B33 4C 8B E9                                mov     r13, rcx

40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 08 FF FF FF 48 81 EC F8 01 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 E0 00 00 00 8B BD 60 01 00 00

00007FF69B2D9410 - 00007FF69A460000 = E79410

LoadPackage

.text:00000001406E0E80 48 8B C4                                mov     rax, rsp
.text:00000001406E0E83 53                                      push    rbx
.text:00000001406E0E84 56                                      push    rsi
.text:00000001406E0E85 48 83 EC 68                             sub     rsp, 68h
.text:00000001406E0E89 48 89 68 08                             mov     [rax+8], rbp
.text:00000001406E0E8D 48 8B EA                                mov     rbp, rdx
.text:00000001406E0E90 4C 89 60 18                             mov     [rax+18h], r12
.text:00000001406E0E94 33 D2                                   xor     edx, edx
.text:00000001406E0E96 4C 89 68 E8                             mov     [rax-18h], r13
.text:00000001406E0E9A 4C 8B E1                                mov     r12, rcx
.text:00000001406E0E9D 4C 89 70 E0                             mov     [rax-20h], r14
.text:00000001406E0EA1 48 8D 48 C8                             lea     rcx, [rax-38h]
.text:00000001406E0EA5 4C 89 78 D8                             mov     [rax-28h], r15
.text:00000001406E0EA9 45 33 ED                                xor     r13d, r13d
.text:00000001406E0EAC 45 8B F8                                mov     r15d, r8d
.text:00000001406E0EAF 4C 89 68 C8                             mov     [rax-38h], r13
.text:00000001406E0EB3 4D 8B F1                                mov     r14, r9

48 8B C4 53 56 48 83 EC 68 48 89 68 08 48 8B EA 4C 89 60 18 33 D2 4C 89 68 E8 4C 8B E1 4C 89 70 E0 48 8D 48 C8 4C 89 78 D8 45 33 ED

00007FF69B2D07A0 - 00007FF69A460000 = E707A0


Create a FSoftObjectPtr and then call FSoftObjectPtr::LoadSynchronous(this).

.text:0000000140260D90                         ; struct UObject *__fastcall FSoftObjectPtr::LoadSynchronous(FSoftObjectPtr *__hidden this)
.text:0000000140260D90                         ?LoadSynchronous@FSoftObjectPtr@@QEBAPEAVUObject@@XZ proc near
.text:0000000140260D90                                                                 ; CODE XREF: UAnimationSharingManager::Initialise(UAnimationSharingSetup const *)+94↑p
.text:0000000140260D90                                                                 ; UAnimSharingInstance::Setup(UAnimationSharingManager *,FPerSkeletonAnimationSharingSetup const &,FAnimationSharingScalability const *,uint)+39↓p ...
.text:0000000140260D90
.text:0000000140260D90                         arg_0           = qword ptr  8
.text:0000000140260D90                         arg_8           = qword ptr  10h
.text:0000000140260D90                         arg_10          = qword ptr  18h
.text:0000000140260D90
.text:0000000140260D90 48 89 5C 24 08                          mov     [rsp+arg_0], rbx
.text:0000000140260D95 48 89 6C 24 10                          mov     [rsp+arg_8], rbp
.text:0000000140260D9A 48 89 74 24 18                          mov     [rsp+arg_10], rsi
.text:0000000140260D9F 57                                      push    rdi
.text:0000000140260DA0 48 83 EC 20                             sub     rsp, 20h
.text:0000000140260DA4 48 8B F9                                mov     rdi, rcx
.text:0000000140260DA7 E8 14 57 49 00                          call    ?Get@FWeakObjectPtr@@QEBAPEAVUObject@@XZ ; FWeakObjectPtr::Get(void)
.text:0000000140260DAC 33 ED                                   xor     ebp, ebp
.text:0000000140260DAE 48 8B F0                                mov     rsi, rax
.text:0000000140260DB1 48 85 C0                                test    rax, rax
.text:0000000140260DB4 75 59                                   jnz     short loc_140260E0F

48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 48 8B F9 ?? ?? ?? ?? ?? 33 ED 48 8B F0 48 85 C0

I don't know how it converts FSoftObjectPath to a Fstring. Maybe use this:
UObject* FSoftObjectPath::TryLoad(FUObjectSerializeContext* InLoadContext) const
	LoadedObject = StaticLoadObject(UObject::StaticClass(), nullptr, *ToString(), nullptr, LOAD_None, nullptr, true, InLoadContext);

Examples:
 FString MaterialFilePath = MountPoint + TEXT("BR_DongChenMingHan_6.BR_DongChenMingHan_6"); // the reference to the object in the engine, not the path of the file
 UMaterial *Material = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *MaterialFilePath));

 UMaterial *mt = LoadObject<UMaterial>(nullptr, TEXT("/Game/Map/Materials/grass.grass"));
 UMaterial *mt = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), nullptr, TEXT("/Game/Map/Materials/grass.grass")));
 
 /**
 * Find or load an object by string name with optional outer and filename specifications.
 * These are optional because the InName can contain all of the necessary information.
 *
 * @param ObjectClass	The class (or a superclass) of the object to be loaded.
 * @param InOuter		An optional object to narrow where to find/load the object from
 * @param Name			String name of the object. If it's not fully qualified, InOuter and/or Filename will be needed
 * @param Filename		An optional file to load from (or find in the file's package object)
 * @param LoadFlags		Flags controlling how to handle loading from disk, from the ELoadFlags enum
 * @param Sandbox		A list of packages to restrict the search for the object
 * @param bAllowObjectReconciliation	Whether to allow the object to be found via FindObject in the case of seek free loading
 * @param InSerializeContext	Additional context when called during serialization
 *
 * @return The object that was loaded or found. nullptr for a failure.
 */
COREUOBJECT_API UObject* StaticLoadObject( UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr, bool bAllowObjectReconciliation = true, FUObjectSerializeContext* InSerializeContext = nullptr );

.text:00000001406E9FA0                         ; struct UObject *__stdcall StaticLoadObject(struct UClass *, struct UObject *, const wchar_t *, const wchar_t *, unsigned int, struct UPackageMap *, bool, struct FUObjectSerializeContext *)
.text:00000001406E9FA0                         ?StaticLoadObject@@YAPEAVUObject@@PEAVUClass@@PEAV1@PEB_W2IPEAVUPackageMap@@_NPEAUFUObjectSerializeContext@@@Z proc near
.text:00000001406E9FA0                                                                 ; CODE XREF: ConstructorHelpersInternal::FindOrLoadObject<UMaterialInterface>(FString &)+247↑p
.text:00000001406E9FA0                                                                 ; ConstructorHelpersInternal::FindOrLoadObject<UPaperTerrainMaterial>(FString &)+247↑p ...
.text:00000001406E9FA0
.text:00000001406E9FA0                         var_300         = dword ptr -300h
.text:00000001406E9FA0                         var_2F8         = qword ptr -2F8h
.text:00000001406E9FA0                         var_2F0         = byte ptr -2F0h
.text:00000001406E9FA0                         var_2E8         = qword ptr -2E8h
.text:00000001406E9FA0                         var_2E0         = byte ptr -2E0h
.text:00000001406E9FA0                         var_2D8         = qword ptr -2D8h
.text:00000001406E9FA0                         var_2D0         = qword ptr -2D0h
.text:00000001406E9FA0                         var_2C8         = qword ptr -2C8h
.text:00000001406E9FA0                         var_2C0         = dword ptr -2C0h
.text:00000001406E9FA0                         var_2B8         = qword ptr -2B8h
.text:00000001406E9FA0                         var_2B0         = qword ptr -2B0h
.text:00000001406E9FA0                         var_2A8         = qword ptr -2A8h
.text:00000001406E9FA0                         var_2A0         = qword ptr -2A0h
.text:00000001406E9FA0                         var_298         = qword ptr -298h
.text:00000001406E9FA0                         var_290         = qword ptr -290h
.text:00000001406E9FA0                         var_288         = qword ptr -288h
.text:00000001406E9FA0                         var_280         = qword ptr -280h
.text:00000001406E9FA0                         var_278         = qword ptr -278h
.text:00000001406E9FA0                         var_270         = qword ptr -270h
.text:00000001406E9FA0                         var_268         = qword ptr -268h
.text:00000001406E9FA0                         var_260         = qword ptr -260h
.text:00000001406E9FA0                         var_258         = qword ptr -258h
.text:00000001406E9FA0                         var_250         = qword ptr -250h
.text:00000001406E9FA0                         Dst             = qword ptr -248h
.text:00000001406E9FA0                         var_240         = dword ptr -240h
.text:00000001406E9FA0                         var_238         = qword ptr -238h
.text:00000001406E9FA0                         var_230         = qword ptr -230h
.text:00000001406E9FA0                         var_228         = qword ptr -228h
.text:00000001406E9FA0                         var_220         = qword ptr -220h
.text:00000001406E9FA0                         var_218         = qword ptr -218h
.text:00000001406E9FA0                         var_210         = qword ptr -210h
.text:00000001406E9FA0                         var_200         = qword ptr -200h
.text:00000001406E9FA0                         var_1F8         = qword ptr -1F8h
.text:00000001406E9FA0                         var_1F0         = qword ptr -1F0h
.text:00000001406E9FA0                         var_1E8         = qword ptr -1E8h
.text:00000001406E9FA0                         var_1E0         = byte ptr -1E0h
.text:00000001406E9FA0                         var_1D8         = byte ptr -1D8h
.text:00000001406E9FA0                         var_1D0         = byte ptr -1D0h
.text:00000001406E9FA0                         var_1C8         = qword ptr -1C8h
.text:00000001406E9FA0                         var_1B8         = byte ptr -1B8h
.text:00000001406E9FA0                         var_1B0         = qword ptr -1B0h
.text:00000001406E9FA0                         var_1A0         = byte ptr -1A0h
.text:00000001406E9FA0                         var_198         = qword ptr -198h
.text:00000001406E9FA0                         var_188         = byte ptr -188h
.text:00000001406E9FA0                         var_180         = qword ptr -180h
.text:00000001406E9FA0                         var_170         = byte ptr -170h
.text:00000001406E9FA0                         var_168         = qword ptr -168h
.text:00000001406E9FA0                         var_158         = byte ptr -158h
.text:00000001406E9FA0                         var_150         = qword ptr -150h
.text:00000001406E9FA0                         var_140         = byte ptr -140h
.text:00000001406E9FA0                         var_130         = qword ptr -130h
.text:00000001406E9FA0                         var_128         = qword ptr -128h
.text:00000001406E9FA0                         var_110         = qword ptr -110h
.text:00000001406E9FA0                         var_108         = qword ptr -108h
.text:00000001406E9FA0                         var_100         = dword ptr -100h
.text:00000001406E9FA0                         var_FC          = dword ptr -0FCh
.text:00000001406E9FA0                         var_F0          = qword ptr -0F0h
.text:00000001406E9FA0                         var_E8          = dword ptr -0E8h
.text:00000001406E9FA0                         var_E0          = dword ptr -0E0h
.text:00000001406E9FA0                         var_D0          = qword ptr -0D0h
.text:00000001406E9FA0                         var_C8          = qword ptr -0C8h
.text:00000001406E9FA0                         var_C0          = dword ptr -0C0h
.text:00000001406E9FA0                         var_B8          = byte ptr -0B8h
.text:00000001406E9FA0                         var_B0          = dword ptr -0B0h
.text:00000001406E9FA0                         var_A0          = qword ptr -0A0h
.text:00000001406E9FA0                         var_98          = qword ptr -98h
.text:00000001406E9FA0                         var_90          = dword ptr -90h
.text:00000001406E9FA0                         var_88          = byte ptr -88h
.text:00000001406E9FA0                         var_80          = dword ptr -80h
.text:00000001406E9FA0                         var_70          = qword ptr -70h
.text:00000001406E9FA0                         var_68          = qword ptr -68h
.text:00000001406E9FA0                         var_60          = dword ptr -60h
.text:00000001406E9FA0                         var_58          = byte ptr -58h
.text:00000001406E9FA0                         var_50          = qword ptr -50h
.text:00000001406E9FA0                         arg_20          = dword ptr  30h
.text:00000001406E9FA0                         arg_28          = qword ptr  38h
.text:00000001406E9FA0                         arg_30          = byte ptr  40h
.text:00000001406E9FA0                         arg_38          = qword ptr  48h
.text:00000001406E9FA0
.text:00000001406E9FA0                         ; __unwind { // __GSHandlerCheck
.text:00000001406E9FA0 40 55                                   push    rbp
.text:00000001406E9FA2 53                                      push    rbx
.text:00000001406E9FA3 56                                      push    rsi
.text:00000001406E9FA4 57                                      push    rdi
.text:00000001406E9FA5 41 54                                   push    r12
.text:00000001406E9FA7 41 55                                   push    r13
.text:00000001406E9FA9 41 56                                   push    r14
.text:00000001406E9FAB 41 57                                   push    r15
.text:00000001406E9FAD 48 8D AC 24 18 FE FF FF                 lea     rbp, [rsp-1E8h]
.text:00000001406E9FB5 48 81 EC E8 02 00 00                    sub     rsp, 2E8h
.text:00000001406E9FBC 48 8B 05 15 74 4D 02                    mov     rax, cs:__security_cookie
.text:00000001406E9FC3 48 33 C4                                xor     rax, rsp
.text:00000001406E9FC6 48 89 85 D0 01 00 00                    mov     [rbp+220h+var_50], rax
.text:00000001406E9FCD 48 8B 85 68 02 00 00                    mov     rax, [rbp+220h+arg_38]
.text:00000001406E9FD4 33 F6                                   xor     esi, esi
.text:00000001406E9FD6 44 8B BD 50 02 00 00                    mov     r15d, [rbp+220h+arg_20]
.text:00000001406E9FDD 48 8B DA                                mov     rbx, rdx
.text:00000001406E9FE0 4C 8B A5 58 02 00 00                    mov     r12, [rbp+220h+arg_28]
.text:00000001406E9FE7 49 8B F9                                mov     rdi, r9
.text:00000001406E9FEA 44 0F B6 AD 60 02 00 00                 movzx   r13d, [rbp+220h+arg_30]
.text:00000001406E9FF2 4D 8B F0                                mov     r14, r8
.text:00000001406E9FF5 89 74 24 60                             mov     [rsp+320h+var_2C0], esi
.text:00000001406E9FF9 48 89 45 C0                             mov     [rbp+220h+var_260], rax
.text:00000001406E9FFD 48 8D 44 24 40                          lea     rax, [rsp+320h+var_2E0]
.text:00000001406EA002 48 89 45 F8                             mov     [rbp+220h+var_228], rax

40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 18 FE FF FF 48 81 EC E8 02 00 00 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 85 D0 01 00 00


.text:00000001414CF400                         ; struct AActor *__usercall UWorld::SpawnActor@<rax>(UWorld *__hidden this@<rcx>, struct UClass *@<rdx>, const struct FVector *@<r8>, const struct FRotator *@<r9>, const struct FActorSpawnParameters *)
.text:00000001414CF400                         ?SpawnActor@UWorld@@QEAAPEAVAActor@@PEAVUClass@@PEBUFVector@@PEBUFRotator@@AEBUFActorSpawnParameters@@@Z proc near
.text:00000001414CF400                                                                 ; CODE XREF: UAnimSharingInstance::Setup(UAnimationSharingManager *,FPerSkeletonAnimationSharingSetup const &,FAnimationSharingScalability const *,uint)+234↑p
.text:00000001414CF400                                                                 ; ULevelVariantSets::GetDirectorInstance(UObject *)+23E↑p ...
.text:00000001414CF400
.text:00000001414CF400                         var_68          = byte ptr -68h
.text:00000001414CF400                         var_58          = xmmword ptr -58h
.text:00000001414CF400                         var_48          = xmmword ptr -48h
.text:00000001414CF400                         var_38          = xmmword ptr -38h
.text:00000001414CF400                         var_28          = qword ptr -28h
.text:00000001414CF400                         arg_20          = qword ptr  28h
.text:00000001414CF400
.text:00000001414CF400                         ; __unwind { // __GSHandlerCheck
.text:00000001414CF400 40 53                                   push    rbx
.text:00000001414CF402 56                                      push    rsi
.text:00000001414CF403 57                                      push    rdi
.text:00000001414CF404 48 83 EC 70                             sub     rsp, 70h
.text:00000001414CF408 48 8B 05 C9 1F 6F 01                    mov     rax, cs:__security_cookie
.text:00000001414CF40F 48 33 C4                                xor     rax, rsp
.text:00000001414CF412 48 89 44 24 60                          mov     [rsp+88h+var_28], rax
.text:00000001414CF417 0F 28 1D A2 30 92 01                    movaps  xmm3, cs:xmmword_142DF24C0
.text:00000001414CF41E 0F 57 D2                                xorps   xmm2, xmm2
.text:00000001414CF421 48 8B B4 24 B0 00 00 00                 mov     rsi, [rsp+88h+arg_20]
.text:00000001414CF429 0F 28 CB                                movaps  xmm1, xmm3
.text:00000001414CF42C 0F 54 1D 6D 30 92 01                    andps   xmm3, cs:xmmword_142DF24A0

40 53 56 57 48 83 EC 70 ?? ?? ?? ?? ?? ?? ?? 48 33 C4 48 89 44 24 60 ?? ?? ?? ?? ?? ?? ?? 0F 57 D2 48 8B B4 24 B0 00 00 00 0F 28 CB

Next we need UWorld. virtual function at vft + 0x140.

.text:00000001406AC8B0                         ; struct UWorld *__fastcall UObject::GetWorld(UObject *__hidden this)
.text:00000001406AC8B0                         ?GetWorld@UObject@@UEBAPEAVUWorld@@XZ proc near
.text:00000001406AC8B0                                                                 ; DATA XREF: .rdata:0000000142070380↓o
.text:00000001406AC8B0                                                                 ; .rdata:0000000142072408↓o ...
.text:00000001406AC8B0 48 8B 49 20                             mov     rcx, [rcx+20h]
.text:00000001406AC8B4 48 85 C9                                test    rcx, rcx
.text:00000001406AC8B7 74 0A                                   jz      short loc_1406AC8C3
.text:00000001406AC8B9 48 8B 01                                mov     rax, [rcx]
.text:00000001406AC8BC 48 FF A0 40 01 00 00                    jmp     qword ptr [rax+140h]
.text:00000001406AC8C3                         ; ---------------------------------------------------------------------------
.text:00000001406AC8C3
.text:00000001406AC8C3                         loc_1406AC8C3:                          ; CODE XREF: UObject::GetWorld(void)+7↑j
.text:00000001406AC8C3 33 C0                                   xor     eax, eax
.text:00000001406AC8C5 C3                                      retn
.text:00000001406AC8C5                         ?GetWorld@UObject@@UEBAPEAVUWorld@@XZ endp