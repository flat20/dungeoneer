#include "console.h"
#include "helpers.h"
#include "uhook.h"
#include <stdlib.h>

#include <GameFramework/InputSettings.h>

ULocalPlayer* UGameInstance::GetFirstGamePlayer() const
{
	return (LocalPlayers.Num() > 0) ? LocalPlayers[0] : nullptr;
}

FName FKey::GetFName() const
{
    return KeyName;
}

//const FKey tilde = EKeys::Tilde("Tilde");
//static const FKey Period;
// const FKey Period("Period");
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

    UInputSettings *InputSettings = (UInputSettings*)FindObjectByName(L"Default__InputSettings", L"InputSettings", nullptr);
    printf("found default InputSettings %llx\n", (uintptr_t)InputSettings);

    struct Temp {
        uint32 Value;
    };
    // Needs Name_Init 
    // name_index for period is 0x0000EE26
    for (FKey &Key : InputSettings->ConsoleKeys) {
        printf("console keys %ws\n", GetName(Key.GetFName()));
        FName a = Key.GetFName();
        Temp *b = (Temp*)&Key;
        b->Value = 0x0000EE26; // Find this index
        //Key = Period;
    }

    for (FKey &Key : InputSettings->ConsoleKeys) {
        printf("console keys after %ws\n", GetName(Key.GetFName()));
    }

    // EKeys::Tilde
    // const FKey EKeys::Tilde("Tilde")
    // EKeys
    // static const FKey Period;
    // static const FKey Tilde;

    // // Find console shortcut
    // auto WorldList = GEngine->GetWorldContexts();
    // printf("asdasd %llx\n", (uintptr_t)WorldList[0].OwningGameInstance);
    // if (WorldList[0].OwningGameInstance == nullptr) {
    //     // return
    // }
    // printf("player? %llx\n", (uintptr_t)WorldList[0].OwningGameInstance->GetFirstGamePlayer());



    // ULocalPlayer *Player = WorldList[0].OwningGameInstance->GetFirstGamePlayer(); // implement
    // printf("actionmap? %llx\n", (uintptr_t)Player->PlayerController->PlayerInput);


    //TArray<struct FInputActionKeyMapping> ActionMappings = Player->PlayerController->PlayerInput->ActionMappings;
    // This crashes:
    //printf("size %d", ActionMappings.Num());

    // for (FInputActionKeyMapping value : ActionMappings) {
    //     printf("ok %ws\n", GetName(value.ActionName));
    //     printf(" %ws\n", GetName(value.Key.GetFName()));
    // }
    // for (auto It = ActionMappings.CreateConstIterator(); It; ++It) {
    //     FInputActionKeyMapping value = *It;
    //     printf("ok %ws\n", GetName(value.ActionName));
    //     printf(" %ws\n", GetName(value.Key.GetFName()));
    // }


	//TArray<struct FInputActionKeyMapping> ActionMappings;
    // FName ActionName;
    // FKey Key;

//     const FKey EKeys::Period("Period");
// const FKey EKeys::Slash("Slash");
// const FKey EKeys::Tilde("Tilde");

    // FString str((TCHAR*)L"abc");
    // console->StartTyping(str);

    return false;
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
    FString str((TCHAR*)L"flat20");

    consoleCommand(console, &str);

    return true;

}


// Set the CVar flags to default to enable them.
static void OnConsoleVariable(const TCHAR *Name, IConsoleObject* CVar)
{
    //if (CVar->TestFlags(ECVF_Cheat)) {
    printf("%ws\n", Name);
    //}
    CVar->SetFlags(ECVF_Default);
}

void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld) {

    // Call original
    origProcessConsoleInput(thisConsoleManager, InInput, Ar, InWorld);

    // Unhook immediately? Or only after we've received the cheat command?
    if (wcscmp((const wchar_t*)InInput, L"flat20") != 0) { // TEXT("flat20")
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

    // // UConsole *console = spy::GEngine->GameViewport->ViewportConsole;
    // // autocomplete::BuildAutocomplete(thisConsoleManager, console);

    // fnEnableConsoleResult(true);

}
