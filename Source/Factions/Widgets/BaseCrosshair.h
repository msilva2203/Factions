// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Widgets/BaseHUD.h"

#include "BaseCrosshair.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API UBaseCrosshair : public UBaseHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Crosshairs")
	void SetPrecision(const float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "Crosshairs")
	void SetCrosshairVisibility(const bool bNewValue);
};
