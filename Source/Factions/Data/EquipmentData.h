// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Factions/BaseActors/BaseEquipment.h"

#include "EquipmentData.generated.h"

UENUM(BlueprintType)
enum class EMaterial : uint8
{
	None		UMETA(DisplayName = "NONE")
};

USTRUCT(BlueprintType)
struct FFactionsEquipmentData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	TSubclassOf<ABaseEquipment> EquipmentSubclass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	int32 DefaultAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	TArray<EMaterial> RecipeMaterials;
};

/**
 * 
 */
UCLASS()
class FACTIONS_API UEquipmentData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	FFactionsEquipmentData Data;
};

USTRUCT(BlueprintType)
struct FInventoryVerticalEquipment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	UEquipmentData* HealthKitData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	UEquipmentData* ExplosiveBombData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	UEquipmentData* FireBombData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	UEquipmentData* SupportBombData;
};

USTRUCT(BlueprintType)
struct FInventoryHorizontalEquipment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	UEquipmentData* ShortWeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Data")
	UEquipmentData* LargeWeaponData;
};
