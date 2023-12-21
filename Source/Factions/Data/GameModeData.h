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
	SupplyRaid		UMETA(DisplayName = "SUPPLY_RAID"),
	Survivors		UMETA(DisplayName = "SURVIVORS"),
	Interrogation	UMETA(DisplayName = "INTERROGATION")
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
