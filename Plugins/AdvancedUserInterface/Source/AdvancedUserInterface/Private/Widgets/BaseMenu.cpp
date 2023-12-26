// Developed by the Factions community


#include "Widgets/BaseMenu.h"

#include "Kismet/KismetInputLibrary.h"


void UBaseMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsFocusable = true;
}

void UBaseMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UBaseMenu::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	Super::NativeOnKeyUp(InGeometry, InKeyEvent);

	if (DisplayedSubMenu)
	{
		const FKey Key = InKeyEvent.GetKey();
		EUINavigation Direction = UKismetInputLibrary::Key_GetNavigationDirectionFromKey(InKeyEvent);
		EUINavigationAction Action = UKismetInputLibrary::Key_GetNavigationActionFromKey(InKeyEvent);

		if (Direction == EUINavigation::Invalid)
		{
			// WASD to control direction
			// Left and Right gamepad shoulders for previous/next

			if (Key == EKeys::A)
				Direction = EUINavigation::Left;
			else if (Key == EKeys::D)
				Direction = EUINavigation::Right;
			else if (Key == EKeys::W)
				Direction = EUINavigation::Up;
			else if (Key == EKeys::S)
				Direction = EUINavigation::Down;
			else if (Key == EKeys::Gamepad_LeftShoulder)
				Direction = EUINavigation::Previous;
			else if (Key == EKeys::Gamepad_RightShoulder)
				Direction = EUINavigation::Next;

		}

		if (Direction != EUINavigation::Invalid)
		{
			// Direction events

			switch (Direction)
			{
			case EUINavigation::Left:
				DisplayedSubMenu->HorizontalOffset(-1);
				break;
			case EUINavigation::Right:
				DisplayedSubMenu->HorizontalOffset(1);
				break;
			case EUINavigation::Up:
				DisplayedSubMenu->VerticalOffset(-1);
				break;
			case EUINavigation::Down:
				DisplayedSubMenu->VerticalOffset(1);
				break;
			case EUINavigation::Next:
				DisplayedSubMenu->Next();
				break;
			case EUINavigation::Previous:
				DisplayedSubMenu->Previous();
				break;
			default:
				break;
			}
		}
		else
		{
			if (!InKeyEvent.IsRepeat())
			{
				// Action events

				if (Action == EUINavigationAction::Invalid)
				{
					// Q and E to navigate menus

					if (Key == EKeys::Q)
						Action = EUINavigationAction::Back;
					else if (Key == EKeys::E)
						Action = EUINavigationAction::Accept;

				}

				if (Action != EUINavigationAction::Invalid)
				{
					switch (Action)
					{
					case EUINavigationAction::Accept:
						DisplayedSubMenu->Accept();
						break;
					case EUINavigationAction::Back:
						DisplayedSubMenu->Back();
						break;
					default:
						break;
					}
				}
				else
				{
					// Custom key events

					const auto KeyName = Key.GetDisplayName();
					auto CustomActions = DisplayedSubMenu->GetSubMenuCustomActions();
					for (auto CustomAction : CustomActions)
					{
						for (auto K : CustomAction.Keys)
						{
							if (KeyName.ToString() == K)
							{
								DisplayedSubMenu->OnCustomAction(CustomAction.ActionIndex);
								break;
							}
						}
					}
				}
			}

		}
	}

	return FReply::Handled();
}

void UBaseMenu::PushSubMenu(UBaseSubMenu* SubMenu)
{
	SubMenus.Add(SubMenu);
	SubMenu->SetVisibility(ESlateVisibility::Collapsed);
	SubMenu->Setup();
}

void UBaseMenu::DisplaySubMenu(UBaseSubMenu* SubMenu)
{
	if (DisplayedSubMenu)
	{
		DisplayedSubMenu->SetSubMenuFocused(false);
	}

	DisplayedSubMenu = SubMenu;
	DisplayedSubMenu->SetSubMenuFocused(true);
	DisplayedSubMenu->Display();
}
