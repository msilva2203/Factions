// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"

#include "BaseEquipment.generated.h"

UCLASS()
class FACTIONS_API ABaseEquipment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseEquipment();

protected:
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

	UPROPERTY(BlueprintReadOnly, Category = "Equipment")
	ACharacter* OwningCharacter;
};
