// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameStates/MatchGameState.h"
#include "Factions/Factions.h"

#include "SupplyRaidGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTeamReinforcementsUpdate, EFactionsTeam, Team, int32, Reinforcements);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamLeadershipUpdated, EFactionsTeam, Team);

/**
 * 
 */
UCLASS()
class FACTIONS_API ASupplyRaidGameState : public AMatchGameState
{
	GENERATED_BODY()
	
public:
	ASupplyRaidGameState(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Supply Raid")
	void SetTeamReinforcements(const EFactionsTeam Team, const int32 NewValue);

	UFUNCTION(BlueprintPure, Category = "Supply Raid")
	int32 GetTeamReinforcements(const EFactionsTeam Team);

	UPROPERTY(ReplicatedUsing = OnRep_Team1Reinforcements, BlueprintReadOnly, Category = "Supply Raid")
	int32 Team1Reinforcements;

	UPROPERTY(ReplicatedUsing = OnRep_Team2Reinforcements, BlueprintReadOnly, Category = "Supply Raid")
	int32 Team2Reinforcements;

	UPROPERTY(BlueprintReadOnly, Category = "Supply Raid")
	EFactionsTeam LeadingTeam;

	UPROPERTY(BlueprintAssignable, Category = "Supply Raid")
	FOnTeamReinforcementsUpdate OnTeamReinforcementsUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Supply Raid")
	FOnTeamLeadershipUpdated OnTeamLeadershipUpdated;

protected:
	UFUNCTION()
	virtual void OnRep_Team1Reinforcements();

	UFUNCTION()
	virtual void OnRep_Team2Reinforcements();

private:
	UFUNCTION()
	void TestTeamLeadership();

};
