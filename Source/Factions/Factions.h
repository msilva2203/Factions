// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"
#include "Factions.generated.h"

//
// ENUMS
//

UENUM(BlueprintType)
enum class EGameMode : uint8
{
	SupplyRaid		UMETA(DisplayName = "SUPPLY_RAID"),
	Survivors		UMETA(DisplayName = "SURVIVORS"),
	Interrogation	UMETA(DisplayName = "INTERROGATION")
};

/**/

//
// STRUCTS
//

USTRUCT(BlueprintType)
struct FGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	EGameMode GameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Mode")
	FText Description;

};

/**/
