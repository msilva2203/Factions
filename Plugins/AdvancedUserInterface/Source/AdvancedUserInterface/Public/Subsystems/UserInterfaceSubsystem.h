// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/LocalPlayerSubsystem.h"

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
	UBaseMenu* PushMenu(TSubclassOf<UBaseMenu> MenuSubclass);

	/**
	* Displays a new menu on the player screen
	* @param MenuToDisplay Reference of the menu you want to display
	*/
	UFUNCTION(BlueprintCallable, Category = "User Interface")
	void DisplayMenu(UBaseMenu* MenuToDisplay);

private:
	UPROPERTY()
	TArray<UBaseMenu*> Menus;
};
