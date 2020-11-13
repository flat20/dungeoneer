#include "console.h"
#include <stdlib.h>

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
    // UClass *ConsoleClass = *(UClass**)&GEngine->ConsoleClass;
    
    return false;
}


bool spy::InitCheatCommands(std::function<void (bool result)> fnResult) {
    fnResult(false);

    return false;
}
