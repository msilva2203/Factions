// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "MapData.generated.h"

USTRUCT(BlueprintType)
struct FFactionsMapData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	FText MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	UTexture2D* DisplayImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	FName LevelName;
};

/**
 * 
 */
UCLASS(BlueprintType)
class FACTIONS_API UMapData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Maps")
	FFactionsMapData Data;
};
