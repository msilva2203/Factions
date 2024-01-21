// Developed by the Factions community


#include "Factions/BaseActors/BaseWeapon.h"
#include "Factions/Pawns/MasterCharacter.h"
#include "Net/UnrealNetwork.h"

ABaseWeapon::ABaseWeapon()
{

}

void ABaseWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseWeapon, MagAmount);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::Equip()
{
	Super::Equip();
}

void ABaseWeapon::Unequip()
{
	Super::Unequip();
}

void ABaseWeapon::SetPrimaryAction(const bool bNewValue)
{
	Super::SetPrimaryAction(bNewValue);

	if (bNewValue)
	{
		// Shoot, reload
		if (bAiming)
		{
			Server_HoldWeaponTrigger();
			if (!HasAuthority())
			{
				HoldWeaponTrigger();
			}
		}
		else
		{
			// TODO: Implement reloading

		}
	}
	else
	{
		// Stop shooting
		Server_ReleaseWeaponTrigger();
		if (!HasAuthority())
		{
			ReleaseWeaponTrigger();
		}
	}
}

void ABaseWeapon::SetSecondaryAction(const bool bNewValue)
{
	Super::SetSecondaryAction(bNewValue);

	bAiming = bNewValue;

	// Stop shooting when stopped aiming
	// Stops the burst fire as well
	ReleaseWeaponTrigger();
	GetWorldTimerManager().ClearTimer(BurstTimerHandle);
}

bool ABaseWeapon::IsWeapon() const
{
	return true;
}

void ABaseWeapon::HoldWeaponTrigger()
{	
	bHoldingTrigger = true;

	if (!bFiring)
	{
		StartFire();
	}
}

void ABaseWeapon::ReleaseWeaponTrigger()
{
	bHoldingTrigger = false;
	//GetWorldTimerManager().ClearTimer(FullAutoTimerHandle);
}

void ABaseWeapon::StartFire()
{
	if (bHoldingTrigger)
	{
		bFiring = true;

		// Reset burst counter
		CurrentBurst = WeaponData->Data.BurstAmount;

		// Fire weapon
		Fire();

		// Start release fire timer
		const float FireTimerRate = 60.0f / WeaponData->Data.FireRate;
		GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ABaseWeapon::ReleaseFire, FireTimerRate, false);

		// Start full auto timer
		const bool bFullAuto = WeaponData->Data.bIsFullAuto;
		if (bFullAuto)
		{

			GetWorldTimerManager().SetTimer(FullAutoTimerHandle, this, &ABaseWeapon::StartFire, FireTimerRate, false);
		}
	}

}

void ABaseWeapon::Fire()
{
	// Decrement burst counter
	CurrentBurst--;
	
	// Start burst timer
	if (CurrentBurst > 0)
	{
		const float BurstTimerRate = 60.0f / WeaponData->Data.BurstRate;
		GetWorldTimerManager().SetTimer(BurstTimerHandle, this, &ABaseWeapon::Fire, BurstTimerRate, false);
	}
	
	// Notify blueprint classes
	OnFire();

	if (HasAmmo())
	{
		// Calls the actual action of firing
		FireAction();

		// Updated weapon ammo
		SetAmount(Amount - 1);
		SetMagAmount(MagAmount - 1);
	}
	
}

void ABaseWeapon::ReleaseFire()
{
	bFiring = false;
}

void ABaseWeapon::FireAction()
{
	if (auto MasterCharacter = Cast<AMasterCharacter>(OwningCharacter))
	{
		const FVector Start = MasterCharacter->PlayerCamera->GetComponentLocation();
		const FVector End = Start + (MasterCharacter->PlayerCamera->GetForwardVector() * 10000.0f);

		FHitResult HitResult(ForceInit);
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(OwningCharacter);
		Params.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, Params);
		if (HitResult.bBlockingHit)
		{
			GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>()->DamageEntity(HitResult.GetActor(), WeaponDamage, GetInstigator(), this);
		}
	}

}

void ABaseWeapon::SetMagAmount(const int32 NewValue)
{
	MagAmount = NewValue;
	OnRep_MagAmount();
}

bool ABaseWeapon::HasAmmo()
{
	return MagAmount > 0;
}

void ABaseWeapon::OnRep_MagAmount()
{
	OnMagAmountUpdated.Broadcast(MagAmount);
}

void ABaseWeapon::Server_HoldWeaponTrigger_Implementation()
{
	HoldWeaponTrigger();
	NetMulticast_HoldWeaponTrigger();
}

bool ABaseWeapon::Server_HoldWeaponTrigger_Validate()
{
	// TODO: Implement RPC validation
	return true;
}

void ABaseWeapon::Server_ReleaseWeaponTrigger_Implementation()
{
	ReleaseWeaponTrigger();
	NetMulticast_ReleaseWeaponTrigger();
}

bool ABaseWeapon::Server_ReleaseWeaponTrigger_Validate()
{
	// TODO: Implement RPC validation
	return true;
}

void ABaseWeapon::NetMulticast_HoldWeaponTrigger_Implementation()
{
	if (!IsLocalInstance() && !HasAuthority())
	{
		HoldWeaponTrigger();
	}
}

void ABaseWeapon::NetMulticast_ReleaseWeaponTrigger_Implementation()
{
	if (!IsLocalInstance() && !HasAuthority())
	{
		ReleaseWeaponTrigger();
	}
}
