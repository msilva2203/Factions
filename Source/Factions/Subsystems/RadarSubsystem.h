// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/LocalPlayerSubsystem.h"

#include "RadarSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FRadarTransform
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	FVector2D Translation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Radar")
	float Angle;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadarIconUpdateDelegate, UBaseRadarIcon*, RadarIcon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadarTransformUpdateDelegate, FRadarTransform, RadarTransform);

/**
 * 
 */
UCLASS()
class FACTIONS_API URadarSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Radar Subsystem")
	void UpdateCenterTransform(FRadarTransform NewTransform);

	UFUNCTION(BlueprintCallable, Category = "Radar Subsytem")
	void SetPhysicalRadius(const float NewRadius);

	UFUNCTION(BlueprintCallable, Category = "Radar Subsytem")
	void SetDisplayRadius(const float NewRadius);

	UPROPERTY(BlueprintReadOnly, Category = "Radar Subsytem")
	FRadarTransform CenterTransform;

	UPROPERTY(BlueprintReadOnly, Category = "Radar Subsystem")
	float PhysicalRadius;

	UPROPERTY(BlueprintReadOnly, Category = "Radar Subsystem")
	float DisplayRadius;

	UPROPERTY(BlueprintAssignable, Category = "Radar Subsytem")
	FOnRadarIconUpdateDelegate OnRadarIconPushed;

	UPROPERTY(BlueprintAssignable, Category = "Radar Subsytem")
	FOnRadarIconUpdateDelegate OnRadarIconRemoved;

	UPROPERTY(BlueprintAssignable, Category = "Radar Subsytem")
	FOnRadarTransformUpdateDelegate OnRadarCenterTransformUpdate;

};
