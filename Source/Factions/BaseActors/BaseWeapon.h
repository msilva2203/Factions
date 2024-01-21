// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/BaseActors/BaseEquipment.h"
#include "Factions/Data/WeaponData.h"

#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMagAmountUpdatedDelegate, int32, NewMagAmount);

/**
 * 
 */
UCLASS()
class FACTIONS_API ABaseWeapon : public ABaseEquipment
{
	GENERATED_BODY()

	ABaseWeapon();
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Weapons")
	void OnFire();

	virtual void Equip() override;
	virtual void Unequip() override;
	virtual void SetPrimaryAction(const bool bNewValue) override;
	virtual void SetSecondaryAction(const bool bNewValue) override;
	virtual bool IsWeapon() const override;

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

	UFUNCTION()
	virtual void SetMagAmount(const int32 NewValue);

	UFUNCTION(BlueprintPure, Category = "Weapons")
	bool HasAmmo();

	UPROPERTY(ReplicatedUsing = "OnRep_MagAmount", BlueprintReadOnly, Category = "Weapons")
	int32 MagAmount;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	UWeaponData* WeaponData;

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	float WeaponDamage;

	UPROPERTY(BlueprintAssignable, Category = "Weapons")
	FOnMagAmountUpdatedDelegate OnMagAmountUpdated;

protected:
	UFUNCTION()
	virtual void OnRep_MagAmount();

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
