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