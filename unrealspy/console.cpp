#include <windows.h>
#include "unreal.h"
#include "unrealspy.h"
#include "util.h"
#include "console.h"

bool InitConsole(SpyData *data) {

    // We should hook the function here.
    // hooks[RefFConsoleManager_ProcessUserConsoleInput] = 
    // spyData.detourProcessUserConsoleInput = &FConsoleManager_ProcessUserConsoleInput;
    // SetHook()

    // Have we already got a console?
    UObject *ViewportConsole = util::GetPropertyValueByPath<UObject>(data->GEngine, data->GEngine, "GameViewport/ViewportConsole");
    if (ViewportConsole != nullptr) {
        return false;
    }

    UObject *GameViewport = util::GetPropertyValueByPath<UObject>(data->GEngine, data->GEngine, "GameViewport");
    if (GameViewport == nullptr) {
        printf("No gameviewport\n");
        return false;
    }

    void** ConsoleClassPtr = (void**)util::GetPropertyValueByPath<uint64>(data->GEngine, data->GEngine, "ConsoleClass");
    if (ConsoleClassPtr == nullptr) {
        printf("No console class\n");
        return false;
    }
    UClass *ConsoleClass = (UClass*)*ConsoleClassPtr;
 
    // printf("New Console properties:\n");
    // util::IterateProperties<UClass>(RealClass, [](UProperty *p) {
    //     printf("  %s %s", getName(p), getName(p->ClassPrivate));
    //     return false;
    // });

    // printf("New Console fields:\n");
    // util::IterateFields(RealClass, [](UField *p) {
    //     printf("  %s %s", getName(p), getName(p->ClassPrivate));
    //     return false;
    // });

    //UClassProperty *p = (UClassProperty*)util::FindObjectByName("ConsoleClass", nullptr);

    FName NameNone{0,0};
    UConsole *console = (UConsole*)data->StaticConstructObject_Internal(ConsoleClass, GameViewport, NameNone, RF_NoFlags, (EInternalObjectFlags)0, nullptr, false, nullptr, false);
    if (console == nullptr) {
        printf("Unable to instantiate console class?\n");
        return false;
    }

    // TODO Clean this up.
    util::IterateProperties(GameViewport, [&](UProperty *p) {
        if (strcmp(util::getName(p), "ViewportConsole") == 0) {
            printf("Found the prop %d\n", p->Offset_Internal);
            *(UObject**)((uint64)GameViewport + p->Offset_Internal) = console;
            // uint8 *pt = (uint8*)GameViewport;
            // pt += p->Offset_Internal;
            // *pt = console;
            // UObject **ptr = (UObject**)(uint64)GameViewport + p->Offset_Internal;
            // *ptr = console;
            return true;
        }
        return false;
    });

    
    UObject *vc = util::GetPropertyValueByPath<UObject>(data->GEngine, data->GEngine, "GameViewport/ViewportConsole");
    if (vc == nullptr) {
        printf("console not set!\n");
        return false;
    }
    printf("console set\n");

    printf("Now issuing command\n");

    UConsole_ConsoleCommand consoleCommand = (UConsole_ConsoleCommand)data->addresses[RefUConsole_ConsoleCommand];

    FString str;
    wchar_t *text = L"flat20";
    str.Data.Data = (TCHAR*)text;
    str.Data.ArrayNum = 7;
    str.Data.ArrayMax = 7;
    consoleCommand(console, &str);
//    data->UConsole_ConsoleCommand((UConsole*)console, &str);
    return true;
}

void __stdcall FConsoleManager_ProcessUserConsoleInput(FConsoleManager* thisConsoleManager, const TCHAR* InInput, void *Ar, void *InWorld) {

//    printf("console input! %ws\n", (wchar*)InInput);
    // Call original
    //tFConsoleManager_ProcessUserConsoleInput puci = (tFConsoleManager_ProcessUserConsoleInput)spyData->origProcessUserConsoleInput;
    //puci(thisConsoleManager, InInput, Ar, InWorld);

    spy::spyData->origProcessUserConsoleInput(thisConsoleManager, InInput, Ar, InWorld);

    // Should be _tstrcmp!?
    if (wcscmp((const wchar_t*)InInput, L"flat20") != 0) { // TEXT("flat20")
        printf("Not flat20\n");
        return;
    }

    printf("Enabling cheats");

    // Disable all cheat flags
    FConsoleManager *cm = (FConsoleManager*)thisConsoleManager;
    for (int i=0; i<cm->ConsoleObjects.ArrayNum; i++) {
        ConsoleManagerObjectsMapElement el = cm->ConsoleObjects.Data[i];
        if (el.IConsoleObject == nullptr) {
            printf("null console object!\n");
            continue;
        }
//        printf("%ws\n", (wchar_t*)el.Name.Data);
        el.IConsoleObject->Flags = ECVF_Default;
//        printf("  %ws\n", (wchar_t*)el.IConsoleObject->Help.Data.Data);
    }

    // Now unhook us
}
