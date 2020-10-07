
#include <stdio.h>
#include <dungeoneer_mod.h>

ModuleInfo modInfo = {
    DUNGEONEER_VERSION,
    "Simple",
};


void UObject_ProcessEvent(UObject* object, UFunction* func, void *params);

// Called when Mod gets loaded
void ModMain(Dungeoneer *dng, Module *mod) {
    printf("simple.cpp\n");
    // Listen for UObject_ProcessEvent (UFunctions being called basically)
    dng->AddFunctionHandler(mod, RefUObject_ProcessEvent, &UObject_ProcessEvent);

    UObject* obj = util::FindObjectByName("Actor", nullptr);

    printf("%s\n", util::getName(obj));
    if (obj != nullptr) {
        printf("%s\n", util::getName(obj->ClassPrivate));
        util::iterate((UStruct*)obj, [](UProperty *p) {
            printf("  %s\n", util::getName(p));
            return false;
        });

        UStruct *cls = (UStruct*)obj;
        for (UField *f = cls->Children; f != nullptr; f = f->Next) {
            printf("iterating fields %s %s\n", util::getName(f), util::getName(f->ClassPrivate));
            
        }

    }
}

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params) {
    // Print out the name of the function and the object it belongs to.
    
    if (strcmp(util::getName(func), "CalculateBaseMagnitude") == 0) {
        printf("simple-mod UObject_ProcessEvent %s.%s::%s() %s %llx\n", util::getName(object->ClassPrivate), util::getName(object), util::getName(func), util::getName(func->ClassPrivate), func->ClassPrivate->ClassCastFlags);
        for (UField *f = func->Children; f != nullptr; f = f->Next) {
            printf(" func params %s %s\n", util::getName(f), util::getName(f->ClassPrivate));
        }
    }

    // Uncomment to show all params for the function. There will be A LOT!
    // iteratePropertiesRecursive(func, params, 0, [&](UProperty *p, void *container, int depth) {
        
    //     printf("%*s", depth, "");
    //     util::dumpProperty(p, container);
    //     printf("\n");

    //     return false;
    // });
}
