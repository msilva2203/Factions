// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Factions/PlayerStates/MasterPlayerState.h"

#include "NameTag.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API UNameTag : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Name Tag")
	void BindPlayerState(AMasterPlayerState* PlayerState);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Name Tag")
	void SetDownDisplayVisibilty(const bool bNewValue);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Name Tag")
	void SetDownPercent(const float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "Name Tag")
	void HideName();
};
