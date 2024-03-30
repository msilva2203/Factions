// Developed by the Factions community


#include "Widgets/BaseHUD.h"

void UBaseHUD::SetHUDVisibility(const bool bNewVisibility, const bool bForce)
{
	if (bForce)
	{
		if (bNewVisibility)
		{
			SetVisibility(ESlateVisibility::HitTestInvisible);
		}
		else
		{
			SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	if (bVisibility != bNewVisibility)
	{
		HandleVisibilityChange(bNewVisibility);
	}
	bVisibility = bNewVisibility;
}
