// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameStates/MasterGameState.h"

#include "MatchGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimeUpdate, int32, Time);

/**
 * 
 */
UCLASS()
class FACTIONS_API AMatchGameState : public AMasterGameState
{
	GENERATED_BODY()
	
public:
	AMatchGameState(const FObjectInitializer& ObjectInitializer);
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Match Game State")
	void SetRemainingTime(const int32 Time, const bool bForce = false);

	UFUNCTION(BlueprintCallable, Category = "Match Game State")
	void SetInProgress(const bool bNewValue);

	UFUNCTION(BlueprintPure, Category = "Match Game State")
	int32 GetRewardActionPoints(const ERewardAction RewardAction);

	UPROPERTY(ReplicatedUsing = OnRep_RemainingTime, BlueprintReadOnly, Category = "Supply Raid")
	int32 RemainingTime;

	UPROPERTY(ReplicatedUsing = OnRep_InProgress, BlueprintReadOnly, Category = "Supply Raid")
	bool bInProgress;

	UPROPERTY(EditAnywhere, Category = "Game Rewards")
	int32 Reward_Down;

	UPROPERTY(EditAnywhere, Category = "Game Rewards")
	int32 Reward_Execution;

	UPROPERTY(EditAnywhere, Category = "Game Rewards")
	int32 Reward_SpecExecution;

	UPROPERTY(EditAnywhere, Category = "Game Rewards")
	int32 Reward_Assist;

	UPROPERTY(EditAnywhere, Category = "Game Rewards")
	int32 Reward_ItemCraft;

	UPROPERTY(EditAnywhere, Category = "Game Rewards")
	int32 Reward_Revive;

	UPROPERTY(BlueprintAssignable, Category = "Supply Raid")
	FOnGameTimeUpdate OnGameTimeUpdate;

protected:
	UFUNCTION()
	virtual void OnRep_RemainingTime();

	UFUNCTION()
	virtual void OnRep_InProgress();

	UFUNCTION()
	virtual void OnGameTimerUpdate();

private:
	UFUNCTION(NetMulticast, Reliable, Category = "Supply Raid")
	void NetMulticast_SetRemainingTime(const int32 Time);
	void NetMulticast_SetRemainingTime_Implementation(const int32 Time);

	UPROPERTY()
	FTimerHandle GameTimer;

};
