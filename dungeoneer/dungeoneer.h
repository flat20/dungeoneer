#pragma once

#include <unrealspy.h>
#include <list>
#include <map>

#define DUNGEONEER_VERSION "0.1"


// struct ProcessEventHandler {
//     char *filterName;
//     tProcessEvent fnHandler;
// };


// ModInfo included in every mod dll. Fetched for info about a mod at runtime.
struct ModuleInfo {
    const char *DungeoneerVersion = DUNGEONEER_VERSION;
    const char *Name;
};

typedef ModuleInfo* (__stdcall *FuncModGetInfo)();

struct Module {
    HMODULE handle;
    std::string filename;
    ModuleInfo *info;
    
    std::map<UE4Reference,void *> functionHandlers;
};


struct Dungeoneer {
    spy::Data *spyData;
    void (__stdcall *AddFunctionHandler)(Module *mod, UE4Reference funcName, void *fnHandler);
};



// TODO Send DungeoneerData?
typedef void (__stdcall *FuncModInit)(Dungeoneer *, Module *);
