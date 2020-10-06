https://forums.unrealengine.com/development-discussion/c-gameplay-programming/42318-opening-a-widget-blueprint-from-c-code

FStringClassReference MyWidgetClassRef(TEXT("/Game/NewWidgetBlueprint.NewWidgetBlueprint_C"));
if ( UClass* MyWidgetClass = MyWidgetClassRef.TryLoadClass<UUserWidget>() )
{
UUserWidget* MyWidget = CreateWidget<UUserWidget>(World / GameInstance / PlayerController, MyWidgetClass);
// Do stuff with MyWidget
} 


https://docs.unrealengine.com/en-US/Programming/Slate/InGameUI/index.html
GEngine->GameViewport->AddViewportWidgetContent(
    SNew(MyWidgetPtr.ToSharedRef())
);