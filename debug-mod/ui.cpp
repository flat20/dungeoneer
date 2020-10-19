#include <imgui.h>
#include <iomanip>
#include <sstream>
#include "debug.h"
#include "ui.h"
#include <util.h>

    //UIData *data; // Manually set. Constructor works?

bool itemsGetter(void* data, int index, const char** name) {
    auto objects = *(std::vector<UObject*>*)data;
    UObject *obj = objects[index];
    std::stringstream ss;
    ss << util::getName(obj);
    if (obj != nullptr) {
        ss << " (" << util::getName(obj->ClassPrivate) << ")";
    }
    ss << " 0x" << std::hex << (uintptr_t)obj;

    *name = ss.str().c_str();

//    std::string objName = (uintptr_t)obj getName()
//    *name = objects[index];
    return true; // false if not found
}

void Draw(void *ctx) {

    ImGui::SetCurrentContext((ImGuiContext*)ctx);
    ImGui::SetNextWindowSize(ImVec2(420, 300), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Debug")) {
        ImGui::End();
        return;
    }

    static int item_current = 0;

//        ImGui::Separator();


    static char findObjectNameText[256];
    static char findObjectClassText[256];
    static std::vector<UObject*>foundObjects;// = {"Something (Class)", "Another (Class)", "Third (Object)"};


    ImGui::InputText("Name", &findObjectNameText[0], sizeof(findObjectNameText));
    ImGui::SameLine();
    if (ImGui::Button("Search")) { // Only if we have some data..
        if (strlen(findObjectNameText) > 2 || strlen(findObjectClassText) > 2) {
            // TODO Copy text if we're serious about this.
            debug::AddExecutor([&](bool result) {
                foundObjects = debug::Search(findObjectNameText, findObjectClassText);
            });
        }
    }

    ImGui::InputText("Class", &findObjectClassText[0], sizeof(findObjectClassText));


    static int obj_current = 0;

    ImGui::Separator();
    static std::vector<char*> props;

    if (ImGui::ListBox("##Objects", &obj_current, &itemsGetter, &foundObjects, foundObjects.size())) {
        printf("item selected %d\n", obj_current);
        props = debug::ListProperties(foundObjects[obj_current]);
        for (auto &p : props) {
            printf("%s\n", p);
        }
    }

    ImGui::Separator();

    static int props_current = 0;
    if (ImGui::ListBox("##Properties", &props_current, &props[0], props.size(), -1)) {
    }

    ImGui::End();
}
