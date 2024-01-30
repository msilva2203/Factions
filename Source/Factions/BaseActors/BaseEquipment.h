// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "BaseEquipment.generated.h"

class UEquipmentData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmountUpdatedDelegate, int32, NewAmount);

UCLASS()
class FACTIONS_API ABaseEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquipment();

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnEquipped();

	UFUNCTION(BlueprintImplementableEvent, Category = "Equipment")
	void OnUnequipped();

	UFUNCTION(BlueprintPure, Category = "Equipment")
	bool IsLocalInstance();

	UFUNCTION()
	virtual void Equip();

	UFUNCTION()
	virtual void Unequip();

	UFUNCTION()
	virtual void ResetEquipment();

	/*
	* Equivalent to pressing or releasing R2/R1
	* Examples: shoot, reload, use medkit, etc...
	*/
	UFUNCTION()
	virtual void SetPrimaryAction(const bool bNewValue);

	/*
	* Equivalent to pressing or releasing L2/R1
	* Examples: aim, etc...
	*/
	UFUNCTION()
	virtual void SetSecondaryAction(const bool bNewValue);

	UFUNCTION(BlueprintPure, Category = "Equipment")
	virtual bool IsWeapon() const;

	UFUNCTION()
	virtual void SetAmount(const int32 NewValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	UEquipmentData* EquipmentData;

	UPROPERTY(ReplicatedUsing = "OnRep_Amount", BlueprintReadOnly, Category = "Equipment")
	int32 Amount;

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	ACharacter* OwningCharacter;

	UPROPERTY(BlueprintAssignable, Category = "Equipment")
	FOnAmountUpdatedDelegate OnAmountUpdated;

protected:
	UFUNCTION()
	virtual void OnRep_Amount();
};
