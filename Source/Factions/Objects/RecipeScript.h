// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RecipeScript.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FACTIONS_API URecipeScript : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void Craft(UInventoryComponent* Inventory);

	UFUNCTION(BlueprintImplementableEvent, Category = "Crafting")
	void OnCraft(UInventoryComponent* Inventory);
};
