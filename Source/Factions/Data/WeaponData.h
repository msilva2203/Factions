// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Factions/Widgets/BaseCrosshair.h"

#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct FFactionsWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bIsFullAuto;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	int32 BurstAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	float BurstRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	int32 MagSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	float PrecisionInterpSpeed;
};

/**
 * 
 */
UCLASS()
class FACTIONS_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Weapons")
	bool IsFullAuto(int32 Level) const;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	int32 GetBurstAmount(int32 Level) const;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	float GetFireRate(int32 Level) const;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	float GetBurstRate(int32 Level) const;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	int32 GetMagSize(int32 Level) const;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	float GetPrecisionInterpSpeed(int32 Level) const;

	UFUNCTION(BlueprintPure, Category = "Weapons")
	const FFactionsWeaponData& GetWeaponLevelData(int32 Level) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FFactionsWeaponData Level1Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FFactionsWeaponData Level2Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FFactionsWeaponData Level3Data;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TSubclassOf<UBaseCrosshair> CrosshairSubclass;
};
