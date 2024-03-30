// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"
#include "Factions/Data/MapData.h"

#include "GameModeData.generated.h"

/**
* Factions gamemode enumeration
*/
UENUM(BlueprintType)
enum class EFactionsGameMode : uint8
{
	None			UMETA(DisplayName = "NONE"),
	SupplyRaid		UMETA(DisplayName = "SUPPLY_RAID"),
	Survivors		UMETA(DisplayName = "SURVIVORS"),
	Interrogation	UMETA(DisplayName = "INTERROGATION")
};

UENUM(BlueprintType)
enum class ERewardAction : uint8
{
	None			UMETA(DisplayName = "NONE"),
	Down			UMETA(DisplayName = "DOWN"),
	Execution		UMETA(DisplayName = "EXECUTION"),
	SpecExecution	UMETA(DisplayName = "SPECIAL_EXECUTION"),
	Assist			UMETA(DisplayName = "ASSIST"),
	ItemCrafted		UMETA(DisplayName = "ITEM_CRAFTED"),
	Revive			UMETA(DisplayName = "REVIVE"),
};

/**
* Factions gamemode data structure
*/
USTRUCT(BlueprintType)
struct FFactionsGameModeData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	EFactionsGameMode GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	FString Alias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	FText Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	TArray<UMapData*> Maps;

};

/**
 * 
 */
UCLASS(BlueprintType)
class FACTIONS_API UGameModeData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameMode Data")
	FFactionsGameModeData Data;
};
