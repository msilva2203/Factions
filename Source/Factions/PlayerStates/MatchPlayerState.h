// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerStates/MasterPlayerState.h"
#include "Factions/Components/InventoryComponent.h"

#include "MatchPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AMatchPlayerState : public AMasterPlayerState
{
	GENERATED_BODY()
	
public:
	AMatchPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInventoryComponent* InventoryComponent;

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void SetIsDead(const bool bNewValue);

	UPROPERTY(ReplicatedUsing = OnRep_IsDead, BlueprintReadOnly, Category = "Match Player State")
	bool bIsDead;

protected:
	UFUNCTION()
	void OnRep_IsDead();
};
