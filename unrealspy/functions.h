#pragma once

#include <diet-ue.h>
#include "offsets.h"

namespace spy {

    namespace functions {

        // Templated subclass with Call which makes it look
        // and feel a bit more like calling a real function. Ex:
        // UConsole_ConsoleCommand.Call(console, command);
        template<typename T>
        class FunctionAddr : public ::offsets::OpcodeAddress {
        public:

            FunctionAddr(const char *InOpcodes) : OpcodeAddress(InOpcodes)
            {        
            }

            // Needed 
            void SetAddress(uintptr_t Address) override {
                ::offsets::OpcodeAddress::SetAddress(Address);
                Call = (T)Address;
            }

            // Ref to function, named Call for neater calling code later.
            T Call;

        };

        typedef UObject* (__fastcall *tStaticConstructObject_Internal)(UClass* Class, UObject* InOuter, FName Name, EObjectFlags SetFlags, EInternalObjectFlags InternalSetFlags, UObject* Template, bool bCopyTransientsFromClassDefaults, void* InstanceGraph, bool bAssumeTemplateIsArchetype);
        extern FunctionAddr<tStaticConstructObject_Internal> StaticConstructObject_Internal;
        typedef void (__thiscall *tUConsole_ConsoleCommand)(UConsole *thisUConsole, const FString *Command);
        extern FunctionAddr<tUConsole_ConsoleCommand> UConsole_ConsoleCommand;
        typedef signed int (__thiscall *tUObject_ProcessEvent)(UObject* thisObject, UFunction* func, void *params);
        extern FunctionAddr<tUObject_ProcessEvent> UObject_ProcessEvent;
        typedef signed int (__thiscall *tAActor_ProcessEvent) (AActor* thisActor, UFunction* func, void *params);
        extern FunctionAddr<tAActor_ProcessEvent> AActor_ProcessEvent;
        typedef void (__thiscall *tAHUD_PostRender) (void *hud);
        extern FunctionAddr<tAHUD_PostRender> AHUD_PostRender;
    }
}
