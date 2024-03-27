// Developed by the Factions community


#include "Factions/Objects/RecipeScript.h"

void URecipeScript::Craft(UInventoryComponent* Inventory)
{
	OnCraft(Inventory);
}
