// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerStates/MasterPlayerState.h"
#include "Factions/Components/InventoryComponent.h"

#include "MatchPlayerState.generated.h"

UENUM(BlueprintType)
enum class EPlayerMatchState : uint8
{
	None			UMETA(DisplayName = "NONE"),
	Loading			UMETA(DisplayName = "LOADING"),
	Spectating		UMETA(DisplayName = "SPECTATING"),
	Playing			UMETA(DisplayName = "PLAYING")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMatchStateUpdatedDelegate, EPlayerMatchState, PlayerMatchState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeadUpdatedDelegate, const bool, bIsDead);

/**
 * 
 */
UCLASS()
class FACTIONS_API AMatchPlayerState : public AMasterPlayerState
{
	GENERATED_BODY()
	
public:
	AMatchPlayerState(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual bool IsEntityDead() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInventoryComponent* InventoryComponent;

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void SetPlayerMatchState(const EPlayerMatchState NewValue);

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void SetIsDead(const bool bNewValue);

	UPROPERTY(ReplicatedUsing = OnRep_PlayerMatchState, BlueprintReadOnly, Category = "Match Player State")
	EPlayerMatchState PlayerMatchState;

	UPROPERTY(ReplicatedUsing = OnRep_IsDead, BlueprintReadOnly, Category = "Match Player State")
	bool bIsDead;

	UPROPERTY(BlueprintAssignable, Category = "Matcg Player State")
	FOnPlayerMatchStateUpdatedDelegate OnPlayerMatchStateUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Matcg Player State")
	FOnPlayerDeadUpdatedDelegate OnPlayerDeadUpdated;

protected:
	UFUNCTION()
	void OnRep_IsDead();

	UFUNCTION()
	void OnRep_PlayerMatchState();
};
