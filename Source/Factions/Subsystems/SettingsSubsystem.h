// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/LocalPlayerSubsystem.h"

#include "SettingsSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API USettingsSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	float FOV;

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	float SensitivityX;

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	float SensitivityY;

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	float SensitivityAimingX;

	UPROPERTY(BlueprintReadOnly, Category = "Settings")
	float SensitivityAimingY;
};
