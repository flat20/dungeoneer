
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
}

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params) {
    // Print out the name of the function and the object it belongs to.
    printf("simple-mod UObject_ProcessEvent %s.%s::%s()\n", util::getName(object->ClassPrivate), util::getName(object), util::getName(func));

    // Uncomment to show all params for the function. There will be A LOT!
    // iteratePropertiesRecursive(func, params, 0, [&](UProperty *p, void *container, int depth) {
        
    //     printf("%*s", depth, "");
    //     util::dumpProperty(p, container);
    //     printf("\n");

    //     return false;
    // });
}
