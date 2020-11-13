#include "console.h"
#include <stdlib.h>

bool spy::InitConsole() {

    return false;
}


bool spy::InitCheatCommands(std::function<void (bool result)> fnResult) {
    fnResult(false);

    return false;
}
