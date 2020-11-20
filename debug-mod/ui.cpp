#include <imgui.h>
#include <iomanip>
#include <sstream>
#include <queue>
#include <mutex> 
#include <utility>
#include "debug.h"
#include "ui.h"

std::queue<std::pair<UObject*,std::vector<UObjectData>>> incomingNodes;
std::mutex treeMtx;
static TreeNode root;

void drawTreeNode(TreeNode node);

bool itemsGetter(void* data, int index, const char** name) {
    auto objects = *(std::vector<UObject*>*)data;
    UObject *obj = objects[index];
    std::stringstream ss;
    ss << spy::GetName(obj);
    if (obj != nullptr) {
        ss << " (" << spy::GetName(obj->GetClass()) << ")";
    }
    ss << " 0x" << std::hex << (uintptr_t)obj;

    *name = ss.str().c_str();

//    std::string objName = (uintptr_t)obj getName()
//    *name = objects[index];
    return true; // false if not found
}

TreeNode *findNodeByUObject(TreeNode *current, UObject *findObject) {
    if ((uintptr_t)current->data.object == (uintptr_t)findObject) {
        return current;
    }
    for (auto &m : current->children) {
        UObject *obj = m.first;
        TreeNode* child = &m.second;
        TreeNode *found = findNodeByUObject(child, findObject);
        if (found != nullptr) {
            return found;
        }
    }
    return nullptr;
}

void loadProperties(TreeNode *node) {
    UObject *object = node->data.object;



    printf("clicked %llx %llx %s\n", uintptr_t(object), (uintptr_t)node, spy::GetName(object));
    // TODO Move to its own function for clarity?
    debug::AddExecutor([object, node](bool result) {

        auto fieldsData = debug::ListProperties(object);
        printf("found  %llx %llx %s\n", uintptr_t(object), (uintptr_t)node, spy::GetName(object));

        std::unique_lock<std::mutex> guard(treeMtx);

        incomingNodes.push(std::pair<UObject*,std::vector<UObjectData>>(object, fieldsData));
        // Create a new node tree and then replace that in drawing thread?
        //node->children.clear();
        // for (auto &fd : fieldsData) {
        //     node->children[fd.object] = TreeNode{fd};
        // }
        guard.unlock();
    });
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

    std::unique_lock<std::mutex> guard(treeMtx);
    if (incomingNodes.size() > 0) {
        auto pair = incomingNodes.front();
        incomingNodes.pop();
        printf("incoming %llx %zd\n", (uintptr_t)pair.first, pair.second.size());
        std::vector<UObjectData> incomingFields = pair.second;
        TreeNode *found = findNodeByUObject(&root, pair.first);
        printf("found? %llx\n", (uintptr_t)found);
        if (found != nullptr) {
            found->children.clear();
            for (auto &it : incomingFields) {
                UObject *obj = it.object;
                found->children[obj] = TreeNode{it};

            }

        }
    }
    guard.unlock();

    ImGui::InputText("Name", &findObjectNameText[0], sizeof(findObjectNameText));
    ImGui::SameLine();
    if (ImGui::Button("Search")) { // Only if we have some data..
        if (strlen(findObjectNameText) > 2 || strlen(findObjectClassText) > 2) {
            std::string objName = findObjectNameText;
            std::string clsName = findObjectClassText;
            // TODO Copy text if we're serious about this.
            debug::AddExecutor([objName,clsName](bool result) {
                foundObjects = debug::Search(objName.c_str(), clsName.c_str());
                // Eventually do this, but we need a map, not a list
                std::lock_guard<std::mutex> guard(treeMtx);
                root.data.name = "Results";
                root.children.clear();
                for (auto &it : foundObjects) {
                    UObject *obj = it;
                    root.children[obj] = TreeNode{UObjectData{obj,nullptr,spy::GetName(obj),spy::GetName(obj->GetClass())}};
                }

            });
        }
    }

    ImGui::InputText("Class", &findObjectClassText[0], sizeof(findObjectClassText));


    static int obj_current = 0;

    ImGui::Separator();

//    static std::vector<UObjectData> fields;

    // if (ImGui::ListBox("##Objects", &obj_current, &itemsGetter, &foundObjects, foundObjects.size())) {
    //     printf("item selected %d\n", obj_current);
    //     UObject *selected = foundObjects[obj_current];
    //     TreeNode &r = root.children[selected];
    //     // root.data.name = util::getName(selected);
    //     // if (selected != nullptr) {
    //     //     root.data.clsName = util::getName(selected->ClassPrivate);
    //     // }

    //     r.children.clear();

    //     auto fields = debug::ListProperties(selected);
    //     for (auto &p : fields) {
    //         r.children[p.object] = TreeNode{p};
    //     }
    // }

    // ImGui::Separator();

    drawTreeNode(root);

    ImGui::End();
}

void drawTreeNode(TreeNode node) {
    
    // if (ImGui::TreeNode("Advanced, with Selectable nodes"))
    // {
    //     static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    //     static bool align_label_with_current_x_position = false;
    //     static bool test_drag_and_drop = false;
    //     ImGui::Text("Hello!");
    //     if (align_label_with_current_x_position)
    //         ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

    //     // 'selection_mask' is dumb representation of what may be user-side selection state.
    //     //  You may retain selection state inside or outside your objects in whatever format you see fit.
    //     // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
    //     /// of the loop. May be a pointer to your own node type, etc.
    //     static int selection_mask = (1 << 2);
    //     int node_clicked = -1;
    //     for (int i = 0; i < 6; i++)
    //     {
    //         // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
    //         ImGuiTreeNodeFlags node_flags = base_flags;
    //         const bool is_selected = (selection_mask & (1 << i)) != 0;
    //         if (is_selected)
    //             node_flags |= ImGuiTreeNodeFlags_Selected;
    //         if (i < 3)
    //         {
    //             // Items 0..2 are Tree Node
    //             bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
    //             if (ImGui::IsItemClicked())
    //                 node_clicked = i;
    //             if (test_drag_and_drop && ImGui::BeginDragDropSource())
    //             {
    //                 ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
    //                 ImGui::Text("This is a drag and drop source");
    //                 ImGui::EndDragDropSource();
    //             }
    //             if (node_open)
    //             {
    //                 ImGui::BulletText("Blah blah\nBlah Blah");
    //                 ImGui::TreePop();
    //             }
    //         }
    //         else
    //         {
    //             // Items 3..5 are Tree Leaves
    //             // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
    //             // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
    //             node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
    //             ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
    //             if (ImGui::IsItemClicked())
    //                 node_clicked = i;
    //             if (test_drag_and_drop && ImGui::BeginDragDropSource())
    //             {
    //                 ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
    //                 ImGui::Text("This is a drag and drop source");
    //                 ImGui::EndDragDropSource();
    //             }
    //         }
    //     }
    //     if (node_clicked != -1)
    //     {
    //         // Update selection state
    //         // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
    //         if (ImGui::GetIO().KeyCtrl)
    //             selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
    //         else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
    //             selection_mask = (1 << node_clicked);           // Click to single-select
    //     }
    //     if (align_label_with_current_x_position)
    //         ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
    //     ImGui::TreePop();
    // }

    if (node.children.size() == 0) {
        ImGui::BulletText(std::string(node.data.name + (node.data.clsName.length() > 0 ? " (" + node.data.clsName + ")" : "")).c_str());
        if (ImGui::IsItemClicked()) {
            loadProperties(&node);
        }
        return;
    }

    if (ImGui::TreeNode(
        std::string(node.data.name + " (" + node.data.clsName + ")").c_str())
        //, ImGuiTreeNodeFlags_None
        ) {
        for (auto &it : node.children) {
            UObject *obj = it.first;
            TreeNode node = it.second;
            drawTreeNode(node);

        }
        ImGui::TreePop();
    }

}