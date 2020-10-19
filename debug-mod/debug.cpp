
#include <stdio.h>
#include <dungeoneer_mod.h>
#include <iterator.h>
#include <queue>
#include <functional>
#include <mutex>

#include "debug.h"
#include "ui.h"

ModuleInfo modInfo = {
    DUNGEONEER_VERSION,
    "Debug",
    &Draw,
};

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params);

//UIData uiData;

tUObject_ProcessEvent origUObject_ProcessEvent;
std::queue<debug::CommandExecutor> commandQueue;
std::mutex commandQueueMtx;

// Called when Mod gets loaded
void ModMain(Dungeoneer *dng, Module *mod) {

    origUObject_ProcessEvent = (tUObject_ProcessEvent)dng->spyData->functionPtrs[RefUObject_ProcessEvent];

    dng->AddFunctionHandler(mod, RefUObject_ProcessEvent, &UObject_ProcessEvent);

}

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params) {
   std::lock_guard<std::mutex> lck(commandQueueMtx);
   if (commandQueue.empty()) {
       return;
   }
   debug::CommandExecutor fn = commandQueue.front();
   commandQueue.pop();
   fn(true);
}


void debug::AddExecutor(CommandExecutor fn) {
    std::lock_guard<std::mutex> lck(commandQueueMtx);
    commandQueue.push(fn);
}

std::vector<UObject*> debug::Search(const char *obj, const char *cls) {
    if (strlen(obj) == 0) {
        obj = nullptr;
    }
    if (strlen(cls) == 0) {
        cls = nullptr;
    }
    std::vector<UObject *> found;
    util::IterateObjectArray([&](UObject *object) {
        // if objectName is requested but doesn't match, continue
        if (obj != nullptr && strstr(util::getName(object), obj) == nullptr) {
            return false;
        }

        // if className is requested but doesn't match, continue
        if (cls != nullptr && strstr(util::getName(object->ClassPrivate), cls) == nullptr) {
            return false;
        }

//        printf("  %s (%s) %llx\n", util::getName(object), util::getName(object->ClassPrivate), (uintptr_t)object);
        found.push_back(object);

        return false; // continue anyway
    });
    return found;

}

std::vector<char*> debug::ListProperties(UObject *object) {

    std::vector<char *> found;
    for (TFieldIterator<UObject> it(object->ClassPrivate); it; ++it) {
        UObject *p = *it;
        found.push_back(util::getName(p));
    }
    return found;

}
