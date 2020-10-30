
#include <stdio.h>
#include <dungeoneer_mod.h>
//#include <iterator.h>

ModuleInfo modInfo = {
    DUNGEONEER_VERSION,
    "Simple",
};


void UObject_ProcessEvent(UObject* object, UFunction* func, void *params);
void AActor_ProcessEvent(AActor* thisActor, UFunction* func, void *params);

tUObject_ProcessEvent origUObject_ProcessEvent;
// tStaticLoadObject StaticLoadObject;
// tStaticLoadClass StaticLoadClass;
// tStaticConstructObject_Internal ConstructObject;
// tUWorld_SpawnActor SpawnActor;
// tUUserWidget_CreateWidget CreateWidget;
// tUUserWidget_AddToViewport AddToViewport;

UEngine *GEngine;
void testing();

// Called when Mod gets loaded
void ModMain(Dungeoneer *dng, Module *mod) {
    printf("simple.cpp\n");

    origUObject_ProcessEvent = (tUObject_ProcessEvent)dng->spyData->functionPtrs[RefUObject_ProcessEvent];

    // StaticLoadObject = (tStaticLoadObject)dng->spyData->functionPtrs[RefStaticLoadObject];
    // StaticLoadClass = (tStaticLoadClass)dng->spyData->functionPtrs[RefStaticLoadClass];
    // ConstructObject = (tStaticConstructObject_Internal)dng->spyData->functionPtrs[RefStaticConstructObject_Internal];
    // SpawnActor = (tUWorld_SpawnActor)dng->spyData->functionPtrs[RefUWorld_SpawnActor];
    // CreateWidget = (tUUserWidget_CreateWidget)dng->spyData->functionPtrs[RefUUserWidget_CreateWidget];
    // AddToViewport = (tUUserWidget_AddToViewport)dng->spyData->functionPtrs[RefUUserWidget_AddToViewport];
    GEngine = dng->spyData->GEngine;

    //printf("%x %x\n", UProperty::StaticClassCastFlags)
    // Listen for UObject_ProcessEvent (UFunctions being called basically)
    dng->AddFunctionHandler(mod, RefUObject_ProcessEvent, &UObject_ProcessEvent);
    //dng->AddFunctionHandler(mod, RefAActor_ProcessEvent, &AActor_ProcessEvent);
}

void UObject_ProcessEvent(UObject* object, UFunction* func, void *params) {
    //testing();
    // // Print out the name of the function and the object it belongs to.
    // if (strstr(util::getName(func), "My") == nullptr) {
    //     return;
    // }
    // printf("%s::", util::getName(object->ClassPrivate));
    // printf("%s.%s(%d) ", util::getName(object), util::getName(func), func->NumParms);

    // printf("iterating this uobject's class' properties\n");
    // for (TFieldIterator<UProperty> it(object->ClassPrivate); it; ++it) {
    //     UProperty *p = *it;
    //     printf("  property: %s\n", util::getName(p));
    // }
    // printf("done\n");
    // for (UObject *outer = object; outer != nullptr; outer = outer->OuterPrivate) {
    //     printf("-%s", util::getName(outer));
    // }
    // printf("\n");

    // // Uncomment to show all params for the function.
    // util::IterateProperties(func, [&](UProperty *p) {

    //     printf("  ");
    //     util::dumpProperty(p, params);
    //     printf("\n");
        
    //     return false;
    // });

    // // Not sure how to get the values of these. It's not in params it seems.
    // printf(" Variables:\n");
    // util::IterateFields(func, [&](UField *f) {
    //     printf(" %s", util::getName(f));
    //     return false;
    // });
    // printf("\n");

}


// void AActor_ProcessEvent(AActor* thisActor, UFunction* func, void *params) {
//     if (strstr(util::getName(func), "My") == nullptr) {
//         return;
//     }
//     printf("%s::", util::getName(thisActor->ClassPrivate));
//     printf("%s.%s(%d) ", util::getName(thisActor), util::getName(func), func->NumParms);
//     printf("\n");
// }

// bool firstTime = true;
// void testing() {
//     using namespace util;
    
//     if (!firstTime) {
//         return;
//     }
//     firstTime = false;

//     // UEnum *levelNames = (UEnum*)FindObjectByName("ELevelNames", nullptr);
//     // printf("%s (%s)\n", getName(levelNames), getName(levelNames->ClassPrivate));
//     // printf("cpp type %ws\n", (wchar_t*)levelNames->CppType.Data.Data);
//     // printf("numNames %d %d\n", levelNames->Names.ArrayNum, levelNames->Names.ArrayMax);
//     // printf("display names function: %llx\n", (uintptr_t)levelNames->EnumDisplayNameFn);

//     // for (int i=0; i<levelNames->Names.ArrayNum; i++) {
//     //     auto pair = levelNames->Names.Data[i];
//     //     printf("%s = %I64d\n", getName(pair.key), pair.value);
//     // }

//     // // UEnum has a virtual:. Maybe it's time to get the full UE4 classes imported..
//     // // virtual bool SetEnums(TArray<TPair<FName, int64>>& InNames, ECppForm InCppForm, bool bAddMaxKeyIfMissing = true);
    
//     // // This code works. The UI appears. But only because BP_ModMapTable is referenced by another item in-game.
//     // // So how can you load up your own assets?
//     // // Using a blueprint I can spawn MyTestBlueprint which makes it show up in the guobjectarray.
//     // // There are two instances. Which is annoying.. But hopefully it doesn't matter which one.
//     // UObject *modMapTable = FindObjectByName("BP_ModMapTable", "BP_ModMapTable_C");
//     // printf("modMapTable: %llx\n", (uintptr_t)modMapTable);
//     // UFunction *myEvent = (UFunction*)FindObjectByName("MyEvent", "Function");
//     // printf("myEvent: %llx\n", (uintptr_t)myEvent);
    
//     // origUObject_ProcessEvent(modMapTable, myEvent, nullptr);
//     // printf("called it?\n");

//     // UObject *dungeonsAssetManager = FindObjectByName("DungeonsAssetManager", "DungeonsAssetManager");
//     // printf("dungeonsAssetManager: %llx\n", (uintptr_t)dungeonsAssetManager);

//     // for (UField *f = dungeonsAssetManager->ClassPrivate->Children; f != nullptr; f = f->Next) {
//     //     printf("  %s (%s)\n", getName(f), getName(f->ClassPrivate));
//     // }


//     // UObject *assetManager = FindObjectByName("AssetManager", "AssetManager");
//     // printf("assetManager: %llx\n", (uintptr_t)assetManager);

//     // for (UField *f = assetManager->ClassPrivate->Children; f != nullptr; f = f->Next) {
//     //     printf("  %s (%s)\n", getName(f), getName(f->ClassPrivate));
//     // }


//     // UObject *inventoryAssetManager = FindObjectByName("DungeonsInventoryAssetManager", "DungeonsInventoryAssetManager");
//     // printf("inventoryAssetManager: %llx\n", (uintptr_t)inventoryAssetManager);

//     // for (UField *f = inventoryAssetManager->ClassPrivate->Children; f != nullptr; f = f->Next) {
//     //     printf("  %s (%s)\n", getName(f), getName(f->ClassPrivate));
//     // }

//     UClass *actorClass = (UClass*)FindObjectByName("Actor", "Class");
//     printf("actor %llx\n", (uintptr_t)actorClass);


//     UClass *widgetClass = (UClass*)FindObjectByName("UserWidget", "Class");
//     printf("widgetClass %llx\n", (uintptr_t)widgetClass);

//     UClass* cls;
//     // THIS works.
//     cls = StaticLoadClass(actorClass, nullptr, (TCHAR*)L"/Game/Decor/Prefabs/ModMapTable/BP_ModMapTable.BP_ModMapTable_C", nullptr, 0, nullptr);
//     cls = StaticLoadClass(actorClass, nullptr, (TCHAR*)L"/Game/UI/ModLevelSelection/MyTestBlueprint.MyTestBlueprint_C", nullptr, 0, nullptr);

//     printf("loaded cls %llx %s %s\n", (uintptr_t)cls, getName(cls), getName(cls->ClassPrivate));
//     FName NameNone{0,0};
//     // AActor *mapTable = (AActor*)ConstructObject(cls, nullptr, NameNone, RF_NoFlags, (EInternalObjectFlags)0, nullptr, false, nullptr, false);

//     // Have we already got a console?
//     UObject *world = util::GetPropertyValueByPath<UObject>(GEngine, GEngine, "GameViewport/World");
//     printf("world %llx %s\n", (uintptr_t)world, getName(world));

//     UObject *gameInstance = util::GetPropertyValueByPath<UObject>(GEngine, GEngine, "GameInstance");
//     printf("gameInstance %llx %s\n", (uintptr_t)gameInstance, getName(gameInstance));

//     // Don't we need a reference to UUserWidget?
//     // UEngine:
//     // 	UPROPERTY()
// 	// class UGameInstance* OwningGameInstance;
//     // Imorgon testa StaticLoadClass UMG och CreateWidget.
//     // Men vad är parentclass för en widget?
    

//     // UserWidget (Class)
//     // DungeonsUserWidget (Class)

//     UClass *myWidgetClass = StaticLoadClass(widgetClass, nullptr, (TCHAR*)L"/Game/UI/ModLevelSelection/UMG_DamageList.UMG_DamageList_C", nullptr, 0, nullptr);
//     printf("myWidgetClass: %llx \n", (uintptr_t)myWidgetClass);

//     //iterator doesn't work.
//     UObject *widget = CreateWidget(gameInstance, myWidgetClass, NameNone);
//     printf("widget: %llx \n", (uintptr_t)widget);
//     AddToViewport(widget, 5000);
//     // UFunction *AddToViewport = nullptr;
//     // for (TFieldIterator<UFunction> fit(widget->ClassPrivate, EFieldIteratorFlags::IncludeSuper); fit; ++fit) {
//     //     UFunction *f = *fit;
//     //     printf("  %llx", (uintptr_t)f);
//     //     printf(" %s (%s)\n", getName(f), getName(f->ClassPrivate));
//     //     if (strcmp(getName(f), "AddToViewport") == 0) {
//     //         AddToViewport = f;
//     //     }
//     // }
//     // printf("done add %llx\n", (uintptr_t)AddToViewport);
//     // origUObject_ProcessEvent(widget, AddToViewport, nullptr);
//     printf("called it?\n");
// //     widget: 1976e5e8b00
// //   UberGraphFrame
// //   OnDamageUpdated
// //   ExecuteUbergraph_UMG_DamageList

// //    Now we need to iterate the parent for this function:
// //	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="User Interface|Viewport", meta=( AdvancedDisplay = "ZOrder" ))
// //	void AddToViewport(int32 ZOrder = 0);

// //     FVector location;
// //     location.X = 18227.0;
// //     location.Y = 8303.0;
// //     location.Z = 11700.0;
// //     FRotator rotation;

// //     FActorSpawnParameters spawnParameters{};
// //     spawnParameters.bNoFail = true;
// //     spawnParameters.bDeferConstruction = false;
// //     spawnParameters.Owner = nullptr;
// //     spawnParameters.Instigator = nullptr;
// //     spawnParameters.Template = nullptr;
// //     spawnParameters.Name.Index = 0;
// //     spawnParameters.Name.Number = 0;
// //     spawnParameters.OverrideLevel = nullptr;
// //     spawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

// // // // ShowDebug !!!!

// //      AActor *actorTable = SpawnActor(world, cls, &location, &rotation, spawnParameters);
// //      printf("actor %llx\n", (uintptr_t)actorTable);



//     // THIS works too!
//     // cls = StaticLoadClass(actorClass, nullptr, (TCHAR*)L"/Game/UI/ModLevelSelection/MyTestBlueprint.MyTestBlueprint_C", nullptr, 0, nullptr);
//     // printf("loaded cls %llx\n", (uintptr_t)cls);

//     // So next: Call a function on my blueprint and see if I can display a widget.
//     // Also next: get the iterator in and print those AssetManager functions
//     // Also: Update mod UI with a "Find Object by name", maybe LoadClass function
//     // Test SpawnActor

//     // dumpObjectArray(util::GUObjectArray);
//     // printf("dumping names\n");
//     // dumpNameEntries();
//     // printf("done\n");

// }