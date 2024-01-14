// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/LocalPlayerSubsystem.h"
#include "Widgets/baseHUD.h"

#include "UserInterfaceSubsystem.generated.h"

// Forward declarations
class UBaseMenu;

/**
 * Use this subsystem to manage the user interface of a local player
 * You can push and display menus
 */
UCLASS()
class ADVANCEDUSERINTERFACE_API UUserInterfaceSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	/**
	* Push a new menu to the subsystem, creating a new instance of the menu subclass
	* @param MenuSubclass The subclass of the menu you want to add to the subsystem
	* @return Reference to the newly created menu
	*/
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	UBaseMenu* PushMenu(TSubclassOf<UBaseMenu> MenuSubclass, const bool bDisplayImmediately = false);

	/**
	* Displays a new menu on the player screen
	* @param MenuToDisplay Reference of the menu you want to display
	*/
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	void DisplayMenu(UBaseMenu* MenuToDisplay);

	/**
	* Push a new HUD element to a HUD layer, creating a new instance of the hud subclass
	* @param HUDSubclass The subclass of the HUD element you want to add to the hud layer
	* @return Reference to the newly created HUD element
	*/
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	UBaseHUD* PushHUD(TSubclassOf<UBaseHUD> HUDSubclass, const bool bDisplayImmediately = false);

	/**
	* Displays every element from the HUD layer specified
	* @param LayerIndex The layer to display
	*/
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	void DisplayHUD(UBaseHUD* HUDToDisplay);

	/**
	* Gets a reference to the HUD specified, returns nullptr if never added to the user interface subsystem
	* @param HUDSubclass The subclass of the HUD element you want to get a reference of
	* @return Reference to the HUD widget
	*/
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	UBaseHUD* GetHUD(TSubclassOf<UBaseHUD> HUDSubclass);

private:
	UPROPERTY()
	TArray<UBaseMenu*> Menus;

	UPROPERTY()
	TArray<UBaseHUD*> HUD;
};
