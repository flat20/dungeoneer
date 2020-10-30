#pragma once

#include <imgui.h>
#include <string>
#include <vector>
#include <list>
#include "ui_config.h"
//#include "dungeoneer.h"

typedef void (*OnLoadPressed)(const char *modName);
typedef void (*OnUnloadPressed)(const char *modName);

struct UIData {
    std::list<FuncConfigDraw> modConfigDraws; // TODO struct
    std::vector<std::string> modNames;
    OnLoadPressed onLoadPressed;
    OnUnloadPressed onUnloadPressed;
    bool modsDisabled;
};

int StartUI(UIData *data);