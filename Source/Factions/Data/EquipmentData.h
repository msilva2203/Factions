// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Factions/BaseActors/BaseEquipment.h"
#include "Factions/Objects/RecipeScript.h"

#include "EquipmentData.generated.h"

UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	HealthKit	UMETA(DisplayName = "HEALTH_KIT"),
	Explosive	UMETA(DisplayName = "EXPLOSIVE"),
	Fire		UMETA(DisplayName = "FIRE"),
	Support		UMETA(DisplayName = "SUPPORT"),
	Utility		UMETA(DisplayName = "UTILITY")
};

UENUM(BlueprintType)
enum class EMaterial : uint8
{
	None		UMETA(DisplayName = "NONE"),
	Alcohol		UMETA(DisplayName = "ALCOHOL"),
	Binding		UMETA(DisplayName = "BINDING"),
	Blade		UMETA(DisplayName = "BLADE"),
	Explosive	UMETA(DisplayName = "EXPLOSIVE"),
	Rag			UMETA(DisplayName = "RAG"),
	Sugar		UMETA(DisplayName = "SUGAR")
};

USTRUCT(BlueprintType)
struct FFactionsCraftingRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TArray<EMaterial> RecipeMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crafting")
	TSubclassOf<URecipeScript> RecipeScriptClass;
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
	FFactionsCraftingRecipe CraftingRecipe;
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
