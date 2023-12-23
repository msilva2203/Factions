// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameStates/MasterGameState.h"
#include "Factions/Factions.h"

#include "SupplyRaidGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameTimeUpdate, int32, Time);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamReinforcementsUpdate, EFactionsTeam, Team, int32, Reinforcements);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamLeadershipUpdated, EFactionsTeam, Team);

/**
 * 
 */
UCLASS()
class FACTIONS_API ASupplyRaidGameState : public AMasterGameState
{
	GENERATED_BODY()
	
	ASupplyRaidGameState();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Supply Raid")
	void SetRemainingTime(const int32 Time);

	UFUNCTION(BlueprintCallable, Category = "Supply Raid")
	void SetInProgress(const bool bNewValue);

	UFUNCTION(BlueprintCallable, Category = "Supply Raid")
	void SetTeamReinforcements(const EFactionsTeam Team, const int32 NewValue);

	UPROPERTY(ReplicatedUsing = OnRep_Team1Reinforcements, BlueprintReadOnly, Category = "Supply Raid")
	int32 Team1Reinforcements;

	UPROPERTY(ReplicatedUsing = OnRep_Team2Reinforcements, BlueprintReadOnly, Category = "Supply Raid")
	int32 Team2Reinforcements;

	UPROPERTY(ReplicatedUsing = OnRep_RemainingTime, BlueprintReadOnly, Category = "Supply Raid")
	int32 RemainingTime;

	UPROPERTY(ReplicatedUsing = OnRep_InProgress, BlueprintReadOnly, Category = "Supply Raid")
	bool bInProgress;

	UPROPERTY(BlueprintAssignable, Category = "Supply Raid")
	FOnGameTimeUpdate OnGameTimeUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Supply Raid")
	FOnTeamReinforcementsUpdate OnTeamReinforcementsUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Supply Raid")
	FOnTeamLeadershipUpdated OnTeamLeadershipUpdated;

protected:
	UFUNCTION()
	virtual void OnRep_Team1Reinforcements();

	UFUNCTION()
	virtual void OnRep_Team2Reinforcements();

	UFUNCTION()
	virtual void OnRep_RemainingTime();

	UFUNCTION()
	virtual void OnRep_InProgress();

	UFUNCTION()
	virtual void OnGameTimerUpdate();

private:
	UFUNCTION(Client, Reliable, Category = "Supply Raid")
	void Client_SetRemainingTime(const int32 Time);

	UFUNCTION()
	void Client_SetRemainingTime_Implementation(const int32 Time);

	UFUNCTION()
	void TestTeamLeadership();

	UPROPERTY()
	FTimerHandle GameTimer;

};
