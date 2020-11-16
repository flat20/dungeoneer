#include "console.h"
#include "helpers.h"
#include "uhook.h"
#include "console_autocomplete.h"
#include <stdlib.h>
#include <wchar.h>

#include <GameFramework/InputSettings.h>

// Most of this code can be used in 4.22. Just needs testing.

void EnableCheatManager();
void SetConsoleKey();

bool spy::InitConsole() {

    printf("init console\n");

    UGameViewportClient *GameViewport = GEngine->GameViewport;
    if (GameViewport == nullptr) {
        printf("no GameViewport\n");
        return false;
    }
    
    // // Have we already got a console?
    if (GameViewport->ViewportConsole != nullptr) {
        printf("no viewportconsole\n");
        return false;
    }

    // Hack to avoid triggering ::StaticClass() inside TSubclassOf.
    // TSubclassOf happens to have only one member, which is a pointer to the UClass.
    UClass *ConsoleClass = *(UClass**)&GEngine->ConsoleClass;
    printf("console class: %ws\n", GetName(ConsoleClass));

    FName NameNone;
    auto ConstructObject = GetFunction<tStaticConstructObject_Internal>(RefStaticConstructObject_Internal);
    UConsole *console = (UConsole*)ConstructObject(ConsoleClass, GameViewport, NameNone, RF_NoFlags, EInternalObjectFlags::None, nullptr, false, nullptr, false);
    if (console == nullptr) {
        printf("Unable to instantiate console class?\n");
        return false;
    }

    GameViewport->ViewportConsole = console;

    SetConsoleKey();

    EnableCheatManager();

    // FString str((TCHAR*)L"abc");
    // console->StartTyping(str);

    return true;
}


std::function<void (bool success)> fnEnableConsoleResult = 0;
tFConsoleManager_ProcessUserConsoleInput origProcessConsoleInput = nullptr;

bool spy::InitCheatCommands(std::function<void (bool result)> fnResult) {
    
    if (GEngine->GameViewport == nullptr || GEngine->GameViewport->ViewportConsole == nullptr) {
        return false;
    }

    bool result = spy::HookFunctionRef(RefFConsoleManager_ProcessUserConsoleInput, &FConsoleManager_ProcessUserConsoleInput, (void**)&origProcessConsoleInput);
    if (result == false) {
        printf("no console hook\n");
        return false;
    }

    fnEnableConsoleResult = fnResult;

    // Send random console command so we can get access to FConsoleManager.
    auto consoleCommand = GetFunction<tUConsole_ConsoleCommand>(RefUConsole_ConsoleCommand);

    UConsole *console = GEngine->GameViewport->ViewportConsole;
    FString str(TEXT("flat20"));

    consoleCommand(console, &str);

    return true;

}


// Set the CVar flags to default to enable them.
static void OnConsoleVariable(const TCHAR *Name, IConsoleObject* CVar)
{
    CVar->SetFlags(ECVF_Default);
}

void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld) {

    // Call original
    origProcessConsoleInput(thisConsoleManager, InInput, Ar, InWorld);

    // Unhook immediately? Or only after we've received the cheat command?
    if (wcscmp(InInput, TEXT("flat20")) != 0) { // TEXT("flat20")
        return;
    }

    bool result = spy::UnhookFunctionRef(RefFConsoleManager_ProcessUserConsoleInput);
    if (result == true) {
        origProcessConsoleInput = nullptr;
    }

    printf("console manager? %llx\n", (uintptr_t)thisConsoleManager);

    // Visit each console var to enable them.
    thisConsoleManager->ForEachConsoleObjectThatStartsWith(
        FConsoleObjectVisitor::CreateStatic(&OnConsoleVariable),
        (TCHAR*)L""
    );

    UConsole *console = spy::GEngine->GameViewport->ViewportConsole;
    autocomplete::BuildAutocomplete(thisConsoleManager, console);

    fnEnableConsoleResult(true);

}

// Implementation
FName FKey::GetFName() const
{
    return KeyName;
}

// TODO Pass in the key to use to open the console.
// Needs FName finder.
void SetConsoleKey() {
    
    UInputSettings *InputSettings = (UInputSettings*)spy::FindObjectByName(TEXT("Default__InputSettings"), TEXT("InputSettings"), nullptr);
    printf("found default InputSettings %llx\n", (uintptr_t)InputSettings);

    // Hack until we can get the FName from the global list.
    struct Temp {
        uint32 Value;
    };
    // Needs Name_Init 
    // name_index for period is 0x0000EE26
    for (FKey &Key : InputSettings->ConsoleKeys) {
        printf("console keys %ws\n", spy::GetName(Key.GetFName()));
        FName a = Key.GetFName();
        Temp *b = (Temp*)&Key;
        b->Value = 0x0000EE26;
        //Key = Period;
    }

    for (FKey &Key : InputSettings->ConsoleKeys) {
        printf("console keys after %ws\n", spy::GetName(Key.GetFName()));
    }

    // EKeys::Tilde
    // const FKey EKeys::Tilde("Tilde")
    // EKeys
    // static const FKey Period;
    // static const FKey Tilde;
}

// impl for access to .LocalPlayers
ULocalPlayer* UGameInstance::GetFirstGamePlayer() const
{
	return (LocalPlayers.Num() > 0) ? LocalPlayers[0] : nullptr;
}

// TODO Not sure if this will ever work. Just testing for Fuser.
void EnableCheatManager() {
    TIndirectArray<FWorldContext> WorldList = spy::GEngine->GetWorldContexts();

    // PlayerController should be HypePlayercontroller something?

    ULocalPlayer *Player = WorldList[0].OwningGameInstance->GetFirstGamePlayer(); // implement
    printf("player ctrler name: %ws\n", spy::GetName(Player->PlayerController));
    printf("cheatmgr? %llx\n", (uintptr_t)Player->PlayerController->CheatManager);

    // TSubClassof has one entry, pointer to the class itself.
    UClass *CheatClass = *(UClass**)&Player->PlayerController->CheatClass;
    printf("cheat cls ? %llx\n", (uintptr_t)CheatClass);
    printf(" name: %ws\n", spy::GetName(CheatClass));

    UObject *cheatManager;
    cheatManager = spy::FindObjectByName(nullptr, TEXT("HypeCheatMgr"), nullptr);
    printf("cm cls ? %llx\n", (uintptr_t)cheatManager);
    printf(" name: %ws\n", spy::GetName(cheatManager));
    
    Player->PlayerController->CheatManager = (UCheatManager*)cheatManager;

    for (TFieldIterator<UFunction> it(cheatManager->GetClass(), EFieldIteratorFlags::ExcludeSuper); it; ++it) {
        UFunction *p = *it;
        printf("  UFunction: %ws flags: %x\n", spy::GetName(p), p->FunctionFlags);
        p->FunctionFlags |= EFunctionFlags::FUNC_Exec;
    }

}