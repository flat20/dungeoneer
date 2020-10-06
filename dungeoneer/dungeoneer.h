#pragma once

#include <unrealspy.h>
#include <list>
#include <map>

#define DUNGEONEER_VERSION "0.1"

typedef std::string FunctionName;

struct ProcessEventHandler {
    char *filterName;
    tProcessEvent fnHandler;
};


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
    
    std::map<FunctionName,void *> functionHandlers;
};


struct Dungeoneer {
    SpyData *spyData;
    void (__stdcall *AddFunctionHandler)(Module *mod, FunctionName funcName, void *fnHandler);
};



// TODO Send DungeoneerData?
typedef void (__stdcall *FuncModInit)(Dungeoneer *, Module *);
