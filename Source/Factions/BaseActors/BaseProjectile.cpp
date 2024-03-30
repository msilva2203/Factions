// Developed by the Factions community


#include "Factions/BaseActors/BaseProjectile.h"

// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	ProjectileComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	ProjectileComponent->SetIsReplicated(true);
	if (ProjectileData)
	{
		ProjectileComponent->InitialSpeed = ProjectileData->Data.Force;
		ProjectileComponent->MaxSpeed = ProjectileData->Data.Force;
		ProjectileComponent->bShouldBounce = ProjectileData->Data.bShouldBounce;
	}

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SetRootComponent(SphereCollisionComponent);
	if (ProjectileData)
	{
		SphereCollisionComponent->SetSphereRadius(ProjectileData->Data.CollisionRadius);
	}
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

