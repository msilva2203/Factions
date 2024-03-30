// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ThrowableProjectileData.generated.h"

class ABaseProjectile;

USTRUCT(BlueprintType)
struct FFactionsProjectileData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float PitchDelta;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Force;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	bool bShouldBounce;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float CollisionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float SimFrequency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<ABaseProjectile> ProjectileClass;
};

/**
 * 
 */
UCLASS()
class FACTIONS_API UThrowableProjectileData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FFactionsProjectileData Data;
};
