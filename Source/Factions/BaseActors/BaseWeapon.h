// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/BaseActors/BaseEquipment.h"
#include "Factions/Data/WeaponData.h"

#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ABaseWeapon : public ABaseEquipment
{
	GENERATED_BODY()

	ABaseWeapon();
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapons")
	void OnFire();

	virtual void Equip() override;
	virtual void Unequip() override;
	virtual void SetPrimaryAction(const bool bNewValue) override;
	virtual void SetSecondaryAction(const bool bNewValue) override;

	UFUNCTION()
	void HoldWeaponTrigger();

	UFUNCTION()
	void ReleaseWeaponTrigger();

	UFUNCTION()
	virtual void StartFire();

	UFUNCTION()
	virtual void Fire();

	UFUNCTION()
	void ReleaseFire();

	UFUNCTION()
	virtual void FireAction();

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	UWeaponData* WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	float WeaponDamage;

private:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_HoldWeaponTrigger();
	void Server_HoldWeaponTrigger_Implementation();
	bool Server_HoldWeaponTrigger_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ReleaseWeaponTrigger();
	void Server_ReleaseWeaponTrigger_Implementation();
	bool Server_ReleaseWeaponTrigger_Validate();

	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_HoldWeaponTrigger();
	void NetMulticast_HoldWeaponTrigger_Implementation();

	UFUNCTION(NetMulticast, Unreliable)
	void NetMulticast_ReleaseWeaponTrigger();
	void NetMulticast_ReleaseWeaponTrigger_Implementation();

	bool bAiming;
	bool bFiring;
	bool bHoldingTrigger;
	int32 CurrentBurst;

	FTimerHandle FireTimerHandle;
	FTimerHandle FullAutoTimerHandle;
	FTimerHandle BurstTimerHandle;
	
};
