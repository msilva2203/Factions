// Developed by the Factions community


#include "Factions/BaseActors/BaseThrowable.h"
#include "Factions/BaseActors/BaseProjectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

ABaseThrowable::ABaseThrowable()
{

}

void ABaseThrowable::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


}

void ABaseThrowable::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseThrowable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!ProjectileData) return;

	if (bAiming)
	{
		// Predicting the throw

		auto ProjData = ProjectileData->Data;

		FVector LaunchVelocity = UKismetMathLibrary::GetForwardVector(OwningCharacter->GetControlRotation().Add(ProjData.PitchDelta, 0.0, 0.0));
		LaunchVelocity *= ProjData.Force;

		FPredictProjectilePathParams Params;
		Params.StartLocation = OwningCharacter->GetActorLocation();
		Params.StartLocation.Z += 80.0;
		Params.LaunchVelocity = LaunchVelocity;
		Params.bTraceWithCollision = true;
		Params.ProjectileRadius = ProjData.CollisionRadius;
		Params.MaxSimTime = ProjData.Time;
		Params.SimFrequency = ProjData.SimFrequency;
		Params.DrawDebugType = EDrawDebugTrace::ForOneFrame;
		Params.ActorsToIgnore.Add(OwningCharacter);

		FPredictProjectilePathResult Result;

		UGameplayStatics::PredictProjectilePath(this, Params, Result);
	}
}

void ABaseThrowable::Equip()
{
	Super::Equip();
}

void ABaseThrowable::Unequip()
{
	Super::Unequip();

	SetSecondaryAction(false);
}

void ABaseThrowable::ResetEquipment()
{
	Super::ResetEquipment();
}

void ABaseThrowable::SetPrimaryAction(const bool bNewValue)
{
	if (bNewValue)
	{
		if (Amount > 0)
		{
			ThrowProjectile(bAiming);
		}
	}
}

void ABaseThrowable::SetSecondaryAction(const bool bNewValue)
{
	if (bNewValue)
	{
		if (Amount > 0) bAiming = true;
	}
	else bAiming = false;
}

bool ABaseThrowable::CanBeEquipped()
{
	return true;
}

bool ABaseThrowable::IsWeapon() const
{
	return false;
}

void ABaseThrowable::OnRep_Amount()
{
	if (Amount <= 0)
	{
		bAiming = false;
	}
}

void ABaseThrowable::ThrowProjectile(const bool bIsAiming)
{
	SetAmount(Amount - 1);

	Server_ThrowProjectile(bAiming);
}

void ABaseThrowable::Server_ThrowProjectile_Implementation(const bool bIsAiming)
{
	if (ProjectileData)
	{
		auto ProjData = ProjectileData->Data;

		FVector Location = OwningCharacter->GetActorLocation();
		Location.Z += 80.0;
		FRotator Rotation = OwningCharacter->GetControlRotation().Add(ProjData.PitchDelta, 0.0, 0.0);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = OwningCharacter;

		GetWorld()->SpawnActor<ABaseProjectile>(ProjData.ProjectileClass, Location, Rotation, SpawnParameters);
	}
	
}

bool ABaseThrowable::Server_ThrowProjectile_Validate(const bool bIsAiming)
{
	// TODO: Implement RPC validation
	return true;
}
