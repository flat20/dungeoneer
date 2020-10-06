#include <windows.h>
#include <Psapi.h>
#include <map>
#include "unrealspy.h"
//#include "unreal_util.h"
#include "util.h"

#include <MinHook.h>



struct Hook {
    uint64 offset;
    void *detour;   // Point this to function
    LPVOID original; // Pointer so we can call the original implementation of the function. Returned after hooking
};

struct Offset {
    uint64 offset;
    void *ptr;      // Pointer to location in running process, once the Offset has been looked up.
};

// We shouldn't force a user into our basic API. Leaving some options
bool SetHook(LPVOID target, LPVOID detour, LPVOID* original);
// Address to target and address to our hook
bool SetHook(uint64 baseAddress, Hook *hook);
bool EnableHook(uint64 baseAddress, uint64 offset);

// const int ofsGNames                 = 0x3FAA768;
// const int ofsGUObjectArray          = 0x3FAEA68;
// const int ofsGEngine                = 0x40AAA68;    // Optional

// const int ofsUObject_ProcessEvent   = 0xE73560;
// const int ofsAActor_ProcessEvent    = 0x19853F0;
// const int ofsAHUD_PostRender        = 0x1BE97B0;

// // Extras
// //const int ofsK2_DrawBox             = 0x1F73D10;
// const int ofsAHUD_DrawRect          = 0x1BD5480;
// const int ofsAHUD_DrawText          = 0x1BD5530;
// const int ofsAHUD_GetTextSize       = 0x1BE4650;

// Map with offsets to lookup?
//std::map<int, void *>offsetPointers;



// Offsets to functions. Name each entry?
std::map<UE4Reference, Hook*> hooks;
std::map<UE4Reference, Offset*> offsets; // Rename to variables? or references?

// Call from within the UE game process
// Sets up GNames global for the util:: namespace to work
bool InitSpy(SpyData *data) {

    // We end up with the same base address as the one we're injected in
    HMODULE dll = GetModuleHandle(NULL);
    uint64 baseAddress = (uint64)dll;
    //HMODULE baseAddress = GetModuleHandleA("Dungeons-Win64-Shipping.exe");
    printf("InitSpy dll %llx\n", baseAddress);
    data->baseAddress = baseAddress;


    HANDLE hProc = GetCurrentProcess();


    //mod.modEntry.modBaseAddr, mod.modEntry.modBaseSize
    //begin = (LPCVOID)baseAddress;



    // return InitSdk("Dungeons.exe", 0x3FB6CB8, 0x3E03AD8);
    offsets["GNames"]           = new Offset{0x3FAC868};
    offsets["GUObjectArray"]    = new Offset{0x3FB0B68};//0x3C15A78}; // wrong?
    offsets["GEngine"]          = new Offset{0x40ACB68};

    offsets["AHUD_DrawRect"]    = new Offset{0x1bd7180};
    offsets["AHUD_DrawText"]    = new Offset{0x1bd7230};
    offsets["AHUD_GetTextSize"] = new Offset{0x1be6350};
    offsets[RefStaticLoadObject]= new Offset{0xe7b5b0}; // UObjectGlobals.h
    offsets[RefStaticLoadClass] = new Offset{0xe7b100}; // UObjectGlobals.h
    offsets[RefLoadPackage]     = new Offset{0xe72490}; // UObjectGlobals.h
    offsets[RefFName_GetNames]  = new Offset{0xCF2D40}; // Maybe find gnames this way?}
    offsets[RefFRawObjectIteratorCtor] = new Offset{0xE0F6F0};

    for(const auto &v: offsets) {
        Offset *offset = v.second;
        offset->ptr = (void*)(baseAddress + offset->offset);
    }


    // data->GNames = *reinterpret_cast<TNameEntryArray**>(offsets["GNames"]->ptr);
    // util::GNames = data->GNames;

    //data->GUObjectArray = (FUObjectArray*)offsets["GUObjectArray"]->ptr;
    data->GEngine = *(UEngine **)offsets["GEngine"]->ptr;

    data->AHUD_DrawRect = (AHUD_DrawRect)offsets["AHUD_DrawRect"]->ptr;
    data->AHUD_DrawText = (AHUD_DrawText)offsets["AHUD_DrawText"]->ptr;
    data->AHUD_GetTextSize = (AHUD_GetTextSize)offsets["AHUD_GetTextSize"]->ptr;
    data->StaticLoadObject = (StaticLoadObject)offsets[RefStaticLoadObject]->ptr;
    data->StaticLoadClass = (StaticLoadClass)offsets[RefStaticLoadClass]->ptr;
    data->LoadPackage = (LoadPackage)offsets[RefLoadPackage]->ptr;
    data->FName_GetNames = (FName_GetNames)offsets[RefFName_GetNames]->ptr;
    data->FRawObjectIteratorCtor = (FRawObjectIteratorCtor)offsets[RefFRawObjectIteratorCtor]->ptr;

    data->GNames = data->FName_GetNames();
    util::GNames = data->GNames;

    // Enough to hold this class we're creating
    char bla[256];
    void **ref = (void**)data->FRawObjectIteratorCtor(&bla[0], false);
    data->GUObjectArray = (FUObjectArray*)*ref;

    printf("Check offsets\n");
    printf("gnames: %llx ptr %llx ofs: %llx\n",  (uint64)data->GNames, (uint64)offsets["GNames"]->ptr, offsets["GNames"]->offset);
    printf("gengine: %s (%s)\n", util::getName(data->GEngine), util::getName(data->GEngine->ClassPrivate));
    printf("guobjectarray: %llx\n", (uint64)data->GUObjectArray);
    printf("NumElements %d\n", data->GUObjectArray->ObjObjects.NumElements);
    printf("NumElementsPerChunk %d\n", data->GUObjectArray->ObjObjects.NumElementsPerChunk);
    printf("NumChunks %d\n", data->GUObjectArray->ObjObjects.NumChunks);
    printf("MaxChunks %d\n", data->GUObjectArray->ObjObjects.MaxChunks);
    printf("MaxElements %d\n", data->GUObjectArray->ObjObjects.MaxElements);
    
    printf("viewport: %llx\n", (DWORD64)data->GEngine->GameViewport);
    if (data->GEngine->GameViewport != nullptr) {
        printf("viewport: %s (%s)\n", util::getName(data->GEngine->GameViewport), util::getName(data->GEngine->GameViewport->ClassPrivate));
    }


    hooks[RefUObject_ProcessEvent]  = new Hook{0xE75250,    data->detourProcessEvent};
    hooks[RefAHUD_PostRender]       = new Hook{0x1BEB4B0,   data->detourPostRender};
    //hooks["GetNames"]               = new Hook{0xCF2D40, data->detourGetNames}; // Maybe find gnames this way?

    // Hook functions
    if (MH_Initialize() != MH_OK) {
        printf("MH_Initialize failed\n");
        return false;
    }

    for(const auto &v: hooks) {
        std::string label = v.first;
        Hook *hook = v.second;
        if (hook->detour == nullptr) {
            continue;
        }

        bool success = SetHook(baseAddress, hook);
        if (success == false) {
            printf("%s hook not set\n", label.c_str());
            return false;
        }
    }

    data->origPostRender = (tPostRender)hooks[RefAHUD_PostRender]->original;
    data->origProcessEvent = (tProcessEvent)hooks[RefUObject_ProcessEvent]->original;
    //data->origGetNames = (tGetNames)hooks["GetNames"]->original;

    // Enable hooks once we have pointers to original functions
    for(const auto &v: hooks) {
        std::string label = v.first;
        Hook *hook = v.second;
        if (hook->detour == nullptr) {
            continue;
        }
        bool success = EnableHook(baseAddress, hook->offset);
        if (success == false) {
            printf("%s hook not enabled\n", label.c_str());
            return false;
        }
    }
    printf("Attached and ready\n");
    return true;
}


bool DeInitSpy(SpyData *data) {

    // Disable hooks
    HMODULE dll = GetModuleHandle(NULL);
    uint64 baseAddress = (uint64)dll;

    // if (data->detourProcessEvent != nullptr) {
    //     if (MH_DisableHook((LPVOID)(baseAddress + ofsUObject_ProcessEvent)) != MH_OK) {
    //         return false;
    //     }
    // }

    // if (data->detourPostRender != nullptr) {
    //     if (MH_DisableHook((LPVOID)(baseAddress + ofsAHUD_PostRender)) != MH_OK) {
    //         return false;
    //     }
    // }

    // Uninitialize MinHook.
    if (MH_Uninitialize() != MH_OK) {
        return false;
    }
    return true;
}

// Address to target and address to our hook
bool SetHook(LPVOID target, LPVOID detour, LPVOID* original) {
    printf("set target: %llx\n", (uint64)target);
    //LPVOID original = nullptr;
    MH_STATUS err;

    err = MH_CreateHook(target, detour, original);
    if (err != MH_OK) {
        printf("MH_CreateHook failed: %d\n", err);
        return false;
    }

    // err = MH_EnableHook(target);
    // if (err != MH_OK) {
    //     printf("MH_EnableHook failed: %d\n", err);
    //     return false;
    // }
    return true;
}


// Address to target and address to our hook
bool SetHook(uint64 baseAddress, Hook *hook) {

    LPVOID target = (LPVOID)(baseAddress + hook->offset);

    return SetHook(target, hook->detour, &hook->original);
}

bool EnableHook(uint64 baseAddress, uint64 offset) {
    LPVOID target = (LPVOID)(baseAddress + offset);
    printf("enable target: %llx\n", (uint64)target);
    MH_STATUS err = MH_EnableHook(target);
    if (err != MH_OK) {
        printf("MH_EnableHook failed: %d\n", err);
        return false;
    }
    return true;
}

// // Do some trickery to figure out where GNames, GUObjectArray and GEngine are.
// void findOffsets() {
// }


// void* __stdcall GetNames() {

//     void *gnames = spyData.origGetNames();
//     printf("getnames? %llx %llx\n", (uint64)gnames, (uint64)spyData.GNames);

//     return gnames;

// }