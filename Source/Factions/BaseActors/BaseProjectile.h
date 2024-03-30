// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Factions/Data/ThrowableProjectileData.h"
#include "Components/SphereComponent.h"

#include "BaseProjectile.generated.h"

UCLASS()
class FACTIONS_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileMovementComponent* ProjectileComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	USphereComponent* SphereCollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UThrowableProjectileData* ProjectileData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
