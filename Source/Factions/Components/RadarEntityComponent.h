// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "Factions/Widgets/BaseRadarIcon.h"
#include "Factions/Subsystems/RadarSubsystem.h"

#include "RadarEntityComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTIONS_API URadarEntityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URadarEntityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Radar Entity Component")
	void PushEntity();

	UFUNCTION(BlueprintCallable, Category = "Radar Entity Component")
	void RemoveEntity();

	UFUNCTION(BlueprintCallable, Category = "Radar Entity Component")
	void UpdateIconTransform(FRadarTransform IconTransform);

	UPROPERTY(EditAnywhere, Category = "Radar Entity Component")
	TSubclassOf<UBaseRadarIcon> RadarIconSubclass;

private:
	UPROPERTY()
	UBaseRadarIcon* Icon;

	UPROPERTY()
	URadarSubsystem* RadarSubsystem;
};
