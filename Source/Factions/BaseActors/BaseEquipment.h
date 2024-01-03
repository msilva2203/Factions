// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

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

	UFUNCTION()
	virtual void Equip();

	UFUNCTION()
	virtual void Unequip();

};
