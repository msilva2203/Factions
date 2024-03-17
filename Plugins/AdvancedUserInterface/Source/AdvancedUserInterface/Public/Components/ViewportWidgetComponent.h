// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Components/SceneComponent.h"
#include "Blueprint/UserWidget.h"

#include "ViewportWidgetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVANCEDUSERINTERFACE_API UViewportWidgetComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UViewportWidgetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Viewport Widget")
	void SetWidget(UUserWidget* NewWidget);

	UPROPERTY(EditAnywhere, Category = "Viewport Widget")
	float SafeZoneX;

	UPROPERTY(EditAnywhere, Category = "Viewport Widget")
	float SafeZoneY;
	
private:
	UPROPERTY()
	UUserWidget* Widget;
};
