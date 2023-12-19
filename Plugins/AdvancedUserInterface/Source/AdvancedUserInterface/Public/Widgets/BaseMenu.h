// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/BaseSubMenu.h"

#include "BaseMenu.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDUSERINTERFACE_API UBaseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	/**
	* Setups this menu
	* Some things you might want to do in this event:
	*   + Push submenus
	*   + Display first submenu in menu
	*   + Setup other UI components
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Menu")
	void Setup();

	/**
	* Push a new submenu to this menu
	* Use this if you want to keep track of submenus
	*/
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void PushSubMenu(UBaseSubMenu* SubMenu);

	/**
	* Displays and focus on a new submenu
	* @param SubMenu Reference to the submenu you want to display and focus
	*/
	UFUNCTION(BlueprintCallable, Category = "Menu")
	void DisplaySubMenu(UBaseSubMenu* SubMenu);

private:
	UPROPERTY()
	UBaseSubMenu* DisplayedSubMenu;

	UPROPERTY()
	TArray<UBaseSubMenu*> SubMenus;
	
};
