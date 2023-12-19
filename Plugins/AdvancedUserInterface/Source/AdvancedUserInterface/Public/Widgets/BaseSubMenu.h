// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/BaseButton.h"

#include "BaseSubMenu.generated.h"


USTRUCT(BlueprintType)
struct FButtonList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button List")
	int32 NavIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button List")
	TArray<UBaseButton*> Buttons;
};

/**
 * 
 */
UCLASS()
class ADVANCEDUSERINTERFACE_API UBaseSubMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetSubMenuFocused(const bool bNewValue);

	/**
	* Setups this submenu
	* Some things you might want to do in this event:
	*   + Create button lists
	*   + Setup other UI components
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Menu")
	void Setup();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void OnMenuFocused();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void OnMenuUnfocused();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void OnDisplay(bool bWasHidden);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void OnHidden(bool bWasHidden);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void VerticalOffset(const int32 Offset);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void HorizontalOffset(const int32 Offset);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void Next();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void Previous();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void Accept();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void Back();

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void NavUpdated(int32 ListIndex, int32 ButtonIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Sub Menu")
	void ButtonClicked(int32 ListIndex, int32 ButtonIndex);

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	void Display();

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	void Hide();

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	int32 CreateButtonList(TArray<UBaseButton*> Buttons);

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	void UpdateButtonListNav(int32 ListIndex, int32 NewIndex, bool bForceUpdate);

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	void OffsetButtonListNav(int32 ListIndex, int32 Offset);

	UFUNCTION(BlueprintCallable, Category = "Sub Menu")
	void SelectButton(int32 ListIndex);

	UFUNCTION()
	void OnButtonHovered(int32 ButtonIndex, int32 ListIndex);

	UFUNCTION()
	void OnButtonClick(int32 ButtonIndex, int32 ListIndex);

private:
	UPROPERTY()
	TArray<FButtonList> ButtonLists;

	UPROPERTY()
	bool bIsFocused;

	UPROPERTY()
	bool bHidden;
	
};
