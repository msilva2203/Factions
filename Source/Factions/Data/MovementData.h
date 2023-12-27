// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "MovementData.generated.h"

USTRUCT(BlueprintType)
struct FFactionsMovementData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	float Speed;
};

/**
 * 
 */
UCLASS()
class FACTIONS_API UMovementData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Data")
	FFactionsMovementData Data;
};
