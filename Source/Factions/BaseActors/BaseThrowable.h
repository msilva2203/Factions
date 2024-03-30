// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"
#include "Factions/BaseActors/BaseEquipment.h"
#include "Factions/Data/ThrowableProjectileData.h"
#include "BaseThrowable.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ABaseThrowable : public ABaseEquipment
{
	GENERATED_BODY()

	ABaseThrowable();
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void Equip() override;
	virtual void Unequip() override;
	virtual void ResetEquipment() override;
	virtual void SetPrimaryAction(const bool bNewValue) override;
	virtual void SetSecondaryAction(const bool bNewValue) override;
	virtual bool CanBeEquipped() override;
	virtual bool IsWeapon() const override;
	virtual void OnRep_Amount() override;

	UFUNCTION()
	void ThrowProjectile(const bool bIsAiming);

	UPROPERTY()
	bool bAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UThrowableProjectileData* ProjectileData;

private:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_ThrowProjectile(const bool bIsAiming);
	void Server_ThrowProjectile_Implementation(const bool bIsAiming);
	bool Server_ThrowProjectile_Validate(const bool bIsAiming);
};
