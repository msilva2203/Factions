// Developed by the Factions community


#include "Widgets/BaseButton.h"


void UBaseButton::NotifyHover()
{
	OnButtonHovered.Broadcast(ButtonIndex, ListIndex);
}

void UBaseButton::NotifyClick()
{
	OnButtonClick.Broadcast(ButtonIndex, ListIndex);
}

int32 UBaseButton::GetButtonIndex() const
{
	return ButtonIndex;
}
