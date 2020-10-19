#pragma once

#include <imgui.h>
#include <string>
#include <vector>

typedef void (*OnLoadPressed)(const char *modName);
typedef void (*OnUnloadPressed)(const char *modName);
typedef std::vector<char *> (*OnSearchPressed)(const char *objName, const char *clsName);

struct UIData {
    std::vector<std::string> modNames;
    OnLoadPressed onLoadPressed;
    OnUnloadPressed onUnloadPressed;
    OnSearchPressed onSearchPressed;
    bool modsDisabled;
};

int StartUI(UIData *data);