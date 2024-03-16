// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Widgets/BaseHUD.h"

#include "DownDisplay.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API UDownDisplay : public UBaseHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Down Display")
	void SetPercent(const float NewValue);
};
