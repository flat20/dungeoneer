//#include "unrealspy.h"
//#include "util.h"
#include "console.h"
//#include <windows.h>

std::function<void (bool success)> fnEnableConsoleResult = 0;
tFConsoleManager_ProcessUserConsoleInput origProcessConsoleInput = nullptr;

// TODO Enabling all commands should be a second function call
bool spy::EnableConsole(std::function<void (bool result)> fnResult) {

    return false;

    // // Have we already got a console?
    // UObject *ViewportConsole = util::GetPropertyValueByPath<UObject>(data.GEngine, data.GEngine, "GameViewport/ViewportConsole");
    // if (ViewportConsole != nullptr) {
    //     return false;
    // }

    // UObject *GameViewport = util::GetPropertyValueByPath<UObject>(data.GEngine, data.GEngine, "GameViewport");
    // if (GameViewport == nullptr) {
    //     printf("No gameviewport\n");
    //     return false;
    // }

    // void** ConsoleClassPtr = (void**)util::GetPropertyValueByPath<uint64>(data.GEngine, data.GEngine, "ConsoleClass");
    // if (ConsoleClassPtr == nullptr) {
    //     printf("No console class\n");
    //     return false;
    // }
    // UClass *ConsoleClass = (UClass*)*ConsoleClassPtr;

    // FName NameNone{0,0};
    // auto ConstructObject = GetFunction<tStaticConstructObject_Internal>(RefStaticConstructObject_Internal);
    // UConsole *console = (UConsole*)ConstructObject(ConsoleClass, GameViewport, NameNone, RF_NoFlags, (EInternalObjectFlags)0, nullptr, false, nullptr, false);
    // if (console == nullptr) {
    //     printf("Unable to instantiate console class?\n");
    //     return false;
    // }

    // // TODO Clean this up.
    // util::IterateProperties(GameViewport, [&](UProperty *p) {
    //     if (strcmp(util::getName(p), "ViewportConsole") == 0) {
    //         *(UObject**)((uint64)GameViewport + p->Offset_Internal) = console;
    //         return true;
    //     }
    //     return false;
    // });

    // UObject *vc = util::GetPropertyValueByPath<UObject>(data.GEngine, data.GEngine, "GameViewport/ViewportConsole");
    // if (vc == nullptr) {
    //     printf("console not set!\n");
    //     return false;
    // }
    // printf("Console enabled\n");

    // bool result = spy::HookFunctionRef(RefFConsoleManager_ProcessUserConsoleInput, &FConsoleManager_ProcessUserConsoleInput, (void**)&origProcessConsoleInput);
    // if (result == false) {
    //     return false;
    // }

    // fnEnableConsoleResult = fnResult;

    // auto consoleCommand = GetFunction<tUConsole_ConsoleCommand>(RefUConsole_ConsoleCommand);

    // FString str;
    // wchar_t *text = L"flat20";
    // str.Data.Data = (TCHAR*)text;
    // str.Data.ArrayNum = 7;
    // str.Data.ArrayMax = 7;
    // consoleCommand(console, &str);

    // return true;
}

void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld) {

//     // Call original
//     origProcessConsoleInput(thisConsoleManager, InInput, Ar, InWorld);

//     // Unhook immediately? Or only after we've received the cheat command?

//     if (wcscmp((const wchar_t*)InInput, L"flat20") != 0) { // TEXT("flat20")
//         return;
//     }

//     bool result = spy::UnhookFunctionRef(RefFConsoleManager_ProcessUserConsoleInput);
//     if (result == true) {
//         origProcessConsoleInput = nullptr;
//     }

//     // Might be useful to save FConsoleManager somewhere, considering how hard it was to get it.

//     // Disable all cheat flags
//     FConsoleManager *cm = (FConsoleManager*)thisConsoleManager;
//     for (auto& el : cm->ConsoleObjects) {
//         ConsoleManagerObjectsMapElement = *el.Value;
//         if (el.IConsoleObject == nullptr) {
//             printf("null console object!\n");
//             continue;
//         }
// //        printf("%ws\n", (wchar_t*)el.Name.Data);
//         el.IConsoleObject->Flags = ECVF_Default;
//     }
// //     for (int i=0; i<cm->ConsoleObjects.Num(); i++) { // Was arraynum
// //         ConsoleManagerObjectsMapElement el = cm->ConsoleObjects.Data[i];
// //         if (el.IConsoleObject == nullptr) {
// //             printf("null console object!\n");
// //             continue;
// //         }
// // //        printf("%ws\n", (wchar_t*)el.Name.Data);
// //         el.IConsoleObject->Flags = ECVF_Default;
// // //        printf("  %ws\n", (wchar_t*)el.IConsoleObject->Help.Data.Data);
// //     }

//     fnEnableConsoleResult(true);
}
