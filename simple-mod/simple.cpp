
#include <stdio.h>
#include <dungeoneer_mod.h>

ModuleInfo modInfo = {
    DUNGEONEER_VERSION,
    "Simple",
};


void UObject_ProcessEvent(UObject* object, UFunction* func, void *params);
void AActor_ProcessEvent(AActor* thisActor, UFunction* func, void *params);

// Called when Mod gets loaded
void ModMain(Dungeoneer *dng, Module *mod) {
    printf("simple.cpp\n");
    // Listen for UObject_ProcessEvent (UFunctions being called basically)
    //dng->AddFunctionHandler(mod, RefUObject_ProcessEvent, &UObject_ProcessEvent);
    dng->AddFunctionHandler(mod, RefAActor_ProcessEvent, &AActor_ProcessEvent);

}

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params) {
    // Print out the name of the function and the object it belongs to.
    printf("%s::", util::getName(object->ClassPrivate));
    printf("%s.%s(%d) ", util::getName(object), util::getName(func), func->NumParms);
    for (UObject *outer = object; outer != nullptr; outer = outer->OuterPrivate) {
        printf("-%s", util::getName(outer));
    }
    printf("\n");

    // Uncomment to show all params for the function.
    util::IterateProperties(func, [&](UProperty *p) {

        printf("  ");
        util::dumpProperty(p, params);
        printf("\n");
        
        return false;
    });

    // Not sure how to get the values of these. It's not in params it seems.
    printf(" Variables:\n");
    util::IterateFields(func, [&](UField *f) {
        printf(" %s", util::getName(f));
        return false;
    });
    printf("\n");

}


void AActor_ProcessEvent(AActor* thisActor, UFunction* func, void *params) {
    printf("%s::", util::getName(thisActor->ClassPrivate));
    printf("%s.%s(%d) ", util::getName(thisActor), util::getName(func), func->NumParms);
    printf("\n");
}