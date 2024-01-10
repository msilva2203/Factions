// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Engine/DataAsset.h"

#include "CameraData.generated.h"

USTRUCT(BlueprintType)
struct FFactionsCameraData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float Distance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DistanceInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float FovOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float FovOffsetInterpSped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ShoulderOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ShoudlerOffsetInterpSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float FollowSpeed;

};

/**
 * 
 */
UCLASS()
class FACTIONS_API UCameraData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Data")
	FFactionsCameraData Data;
};
