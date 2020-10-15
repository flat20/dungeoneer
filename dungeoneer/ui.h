#pragma once

#include <imgui.h>
#include <string>
#include <vector>

typedef void (*OnLoadPressed)(const char *modName);
typedef void (*OnUnloadPressed)(const char *modName);

struct UIData {
    std::vector<std::string> modNames;
    OnLoadPressed onLoadPressed;
    OnUnloadPressed onUnloadPressed;
    bool modsDisabled;
};

int StartUI(UIData *data);