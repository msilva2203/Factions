// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUSERINTERFACE_API UBaseHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Base HUD")
	void SetHUDVisibility(const bool bNewVisibility, const bool bForce);

	UFUNCTION(BlueprintImplementableEvent, Category = "Base HUD")
	void HandleVisibilityChange(const bool bNewValue);

	UPROPERTY(BlueprintReadOnly, Category = "Base HUD")
	bool bVisibility;
};
