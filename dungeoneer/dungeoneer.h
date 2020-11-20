#pragma once

#include <unrealspy.h>
#include <helpers.h>
#include <uhook.h>
#include <list>
#include <map>
#include "ui_config.h"

#define DUNGEONEER_VERSION "0.1.1"

// ModInfo included in every mod dll. Fetched for info about a mod at runtime.
struct ModuleInfo {
    const char *DungeoneerVersion = DUNGEONEER_VERSION;
    const char *Name;
    FuncConfigDraw ConfigDraw = nullptr; // Optional ImGui Draw() for settings
};

typedef ModuleInfo* (__stdcall *FuncModGetInfo)();

struct Module {
    void* handle;   // HMODULE actually
    std::string filename;
    ModuleInfo *info;
    
    std::map<offsets::OpcodeAddress*,void *> functionHandlers;
};

// Init struct for mods.
struct Dungeoneer {

    FUObjectArray *GUObjectArray;
    TNameEntryArray *GNames;
    UEngine* GEngine;

    spy::Data *spyData;
    void (__stdcall *AddFunctionHandler)(Module *mod, offsets::OpcodeAddress* func, void *fnHandler);
};



// TODO Send DungeoneerData?
typedef void (__stdcall *FuncModInit)(Dungeoneer *, Module *);
