// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "BaseButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonActionDelegate, int32, ButtonIndex, int32, ListIndex);

/**
 * 
 */
UCLASS()
class ADVANCEDUSERINTERFACE_API UBaseButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void SetHovered(bool bNewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void Selected();

	UFUNCTION(BlueprintCallable, Category = "Button")
	void NotifyHover();

	UFUNCTION(BlueprintCallable, Category = "Button")
	void NotifyClick();

	UFUNCTION(BlueprintPure, Category = "Button")
	int32 GetButtonIndex() const;

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonActionDelegate OnButtonHovered;

	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonActionDelegate OnButtonClick;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
	int32 ButtonIndex;

	UPROPERTY()
	int32 ListIndex;

};
