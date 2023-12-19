// Developed by the Factions community


#include "Widgets/BaseSubMenu.h"


void UBaseSubMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

	bHidden = true;
}

void UBaseSubMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseSubMenu::SetSubMenuFocused(const bool bNewValue)
{
	if (bNewValue != bIsFocused)
	{
		bIsFocused = bNewValue;
		if (bIsFocused)
		{
			OnMenuFocused();
			SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			OnMenuUnfocused();
			SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}
}

void UBaseSubMenu::Display()
{
	OnDisplay(bHidden);
	bHidden = false;
}

void UBaseSubMenu::Hide()
{
	OnHidden(bHidden);
	bHidden = true;
}

int32 UBaseSubMenu::CreateButtonList(TArray<UBaseButton*> Buttons)
{
	if (!Buttons.IsEmpty())
	{
		FButtonList NewList;
		NewList.Buttons = Buttons;
		NewList.NavIndex = 0;

		ButtonLists.Add(NewList);

		const int32 ListIndex = ButtonLists.Num() - 1;

		for (int i = 0; i < Buttons.Num(); i++)
		{
			auto Btn = Buttons[i];

			Btn->ButtonIndex = i;
			Btn->ListIndex = ListIndex;
			Btn->OnButtonHovered.AddDynamic(this, &UBaseSubMenu::OnButtonHovered);
			Btn->OnButtonClick.AddDynamic(this, &UBaseSubMenu::OnButtonClick);

			Btn->SetHovered(false);
		}

		return ListIndex;
	}
	return -1;
}

void UBaseSubMenu::UpdateButtonListNav(int32 ListIndex, int32 NewIndex, bool bForceUpdate)
{
	FButtonList& List = ButtonLists[ListIndex];

	const int32 Index = List.NavIndex;
	TArray<UBaseButton*> Buttons = List.Buttons;

	if (NewIndex < 0)
	{
		NewIndex = Index;
		bForceUpdate = true;
	}

	if (Index != NewIndex || bForceUpdate)
	{
		auto Button = Buttons[Index];
		Button->SetHovered(false);

		Button = Buttons[NewIndex];
		Button->SetHovered(true);

		NavUpdated(ListIndex, NewIndex);
	}

	List.NavIndex = NewIndex;
}

void UBaseSubMenu::OffsetButtonListNav(int32 ListIndex, int32 Offset)
{
	FButtonList& List = ButtonLists[ListIndex];

	const int32 Index = List.NavIndex;
	TArray<UBaseButton*> Buttons = List.Buttons;
	const int32 Max = Buttons.Num() - 1;

	int32 NewIndex = Index + Offset;

	if (NewIndex < 0)
	{
		NewIndex = Max;
	}
	else if (NewIndex > Max)
	{
		NewIndex = 0;
	}

	UpdateButtonListNav(ListIndex, NewIndex, false);
}

void UBaseSubMenu::SelectButton(int32 ListIndex)
{
	FButtonList& List = ButtonLists[ListIndex];
	const int32 Index = List.NavIndex;

	OnButtonClick(Index, ListIndex);
}

void UBaseSubMenu::OnButtonHovered(int32 ButtonIndex, int32 ListIndex)
{
	if (bIsFocused)
	{
		UpdateButtonListNav(ListIndex, ButtonIndex, false);
	}
}

void UBaseSubMenu::OnButtonClick(int32 ButtonIndex, int32 ListIndex)
{
	if (bIsFocused)
	{
		ButtonLists[ListIndex].Buttons[ButtonIndex]->Selected();
		ButtonClicked(ListIndex, ButtonIndex);
	}
}
