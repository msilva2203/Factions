// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

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
};

/**
 * 
 */
UCLASS()
class FACTIONS_API UWeaponData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	FFactionsWeaponData Data;
};
