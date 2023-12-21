// Developed by the Factions community


#include "Subsystems/UserInterfaceSubsystem.h"

#include "Widgets/BaseMenu.h"
#include "Blueprint/WidgetBlueprintLibrary.h"


void UUserInterfaceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Warning, TEXT("User Interface Subsystem initialized"));
}

UBaseMenu* UUserInterfaceSubsystem::PushMenu(TSubclassOf<UBaseMenu> MenuSubclass)
{
	auto Owner = GetLocalPlayer()->PlayerController.Get();
	auto Menu = CreateWidget<UBaseMenu>(Owner, MenuSubclass);

	if (Menu)
	{
		Menu->AddToViewport();
		Menu->SetVisibility(ESlateVisibility::Collapsed);

		Menus.Add(Menu);

		Menu->Setup();
	}

	return Menu;
}

void UUserInterfaceSubsystem::DisplayMenu(UBaseMenu* MenuToDisplay)
{
	for (auto Menu : Menus)
	{
		if (Menu == MenuToDisplay)
		{
			auto Owner = GetLocalPlayer()->PlayerController.Get();

			Menu->SetVisibility(ESlateVisibility::Visible);
			Menu->SetFocus();

			UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(Owner, Menu);
		}
	}
}

UBaseHUD* UUserInterfaceSubsystem::PushHUD(TSubclassOf<UBaseHUD> HUDSubclass)
{
	auto Owner = GetLocalPlayer()->PlayerController.Get();
	auto Element = CreateWidget<UBaseHUD>(Owner, HUDSubclass);

	if (Element)
	{
		Element->AddToViewport();
		Element->SetVisibility(ESlateVisibility::Collapsed);

		HUD.Add(Element);
	}

	return Element;
}

void UUserInterfaceSubsystem::DisplayHUD(UBaseHUD* HUDToDisplay)
{
	for (auto Element : HUD)
	{
		if (Element == HUDToDisplay)
		{
			Element->SetVisibility(ESlateVisibility::Visible);
		}
	}
}
