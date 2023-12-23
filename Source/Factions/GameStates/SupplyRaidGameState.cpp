// Developed by the Factions community


#include "Factions/GameStates/SupplyRaidGameState.h"

#include "Net/UnrealNetwork.h"

#define DEFAULT_TEAM_REINFORCEMENTS 20
#define DEFAULT_REMAINING_TIME 1200

ASupplyRaidGameState::ASupplyRaidGameState() :
	Team1Reinforcements(DEFAULT_TEAM_REINFORCEMENTS),
	Team2Reinforcements(DEFAULT_TEAM_REINFORCEMENTS),
	RemainingTime(DEFAULT_REMAINING_TIME)
{
}

void ASupplyRaidGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(ASupplyRaidGameState, Team1Reinforcements);
	DOREPLIFETIME(ASupplyRaidGameState, Team2Reinforcements);
	DOREPLIFETIME_CONDITION(ASupplyRaidGameState, RemainingTime, COND_InitialOnly);
	DOREPLIFETIME(ASupplyRaidGameState, bInProgress);

}

void ASupplyRaidGameState::BeginPlay()
{
	Super::BeginPlay();

	OnRep_Team1Reinforcements();
	OnRep_Team2Reinforcements();
	OnRep_RemainingTime();
}

void ASupplyRaidGameState::SetRemainingTime(const int32 Time)
{
	if (GetWorld()->GetNetMode() < ENetMode::NM_Client)
	{
		RemainingTime = Time;
		OnRep_RemainingTime();
	}
}

void ASupplyRaidGameState::SetInProgress(const bool bNewValue)
{
	if (GetWorld()->GetNetMode() < ENetMode::NM_Client)
	{
		bInProgress = bNewValue;
		OnRep_InProgress();
	}
}

void ASupplyRaidGameState::SetTeamReinforcements(const EFactionsTeam Team, const int32 NewValue)
{
	if (GetWorld()->GetNetMode() < ENetMode::NM_Client)
	{
		switch (Team)
		{
		case EFactionsTeam::Enemy:
		case EFactionsTeam::None:
			break;
		case EFactionsTeam::Team01:
			Team1Reinforcements = NewValue;
			OnRep_Team1Reinforcements();
			break;
		case EFactionsTeam::Team02:
			Team2Reinforcements = NewValue;
			OnRep_Team2Reinforcements();
			break;
		default:
			break;
		}
	}
}

void ASupplyRaidGameState::OnRep_Team1Reinforcements()
{
	OnTeamReinforcementsUpdate.Broadcast(EFactionsTeam::Team01, Team1Reinforcements);
	TestTeamLeadership();
}

void ASupplyRaidGameState::OnRep_Team2Reinforcements()
{
	OnTeamReinforcementsUpdate.Broadcast(EFactionsTeam::Team02, Team2Reinforcements);
	TestTeamLeadership();
}

void ASupplyRaidGameState::OnRep_RemainingTime()
{
	OnGameTimeUpdate.Broadcast(RemainingTime);
}

void ASupplyRaidGameState::OnRep_InProgress()
{
	if (bInProgress)
	{
		GetWorld()->GetTimerManager().SetTimer(GameTimer, this, &ASupplyRaidGameState::OnGameTimerUpdate, 1.0f, true, 1.0f);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(GameTimer);
	}
}

void ASupplyRaidGameState::OnGameTimerUpdate()
{
	RemainingTime--;
	OnRep_RemainingTime();
}

void ASupplyRaidGameState::Client_SetRemainingTime_Implementation(const int32 Time)
{
	RemainingTime = Time;
	OnRep_RemainingTime();
}

void ASupplyRaidGameState::TestTeamLeadership()
{
	if (Team1Reinforcements > Team2Reinforcements)
	{
		OnTeamLeadershipUpdated.Broadcast(EFactionsTeam::Team01);
		return;
	}
	if (Team2Reinforcements > Team1Reinforcements)
	{
		OnTeamLeadershipUpdated.Broadcast(EFactionsTeam::Team02);
		return;
	}
	if (Team1Reinforcements == Team2Reinforcements)
	{
		OnTeamLeadershipUpdated.Broadcast(EFactionsTeam::None);
		return;
	}
}
