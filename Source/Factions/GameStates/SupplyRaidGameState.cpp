// Developed by the Factions community


#include "Factions/GameStates/SupplyRaidGameState.h"

#include "Net/UnrealNetwork.h"

#define DEFAULT_TEAM_REINFORCEMENTS 20
#define DEFAULT_REMAINING_TIME 1200

ASupplyRaidGameState::ASupplyRaidGameState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	Team1Reinforcements(DEFAULT_TEAM_REINFORCEMENTS),
	Team2Reinforcements(DEFAULT_TEAM_REINFORCEMENTS)
{
}

void ASupplyRaidGameState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(ASupplyRaidGameState, Team1Reinforcements);
	DOREPLIFETIME(ASupplyRaidGameState, Team2Reinforcements);

}

void ASupplyRaidGameState::BeginPlay()
{
	Super::BeginPlay();

	OnRep_Team1Reinforcements();
	OnRep_Team2Reinforcements();
	OnRep_RemainingTime();
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

		ForceNetUpdate();
	}
}

int32 ASupplyRaidGameState::GetTeamReinforcements(const EFactionsTeam Team)
{
	switch (Team)
	{
	case EFactionsTeam::None:
	case EFactionsTeam::Enemy:
		return -1;
	case EFactionsTeam::Team01:
		return Team1Reinforcements;
	case EFactionsTeam::Team02:
		return Team2Reinforcements;
	default:
		return -1;
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

void ASupplyRaidGameState::TestTeamLeadership()
{
	EFactionsTeam Leader = EFactionsTeam::None;
	if (Team1Reinforcements > Team2Reinforcements)
	{
		Leader = EFactionsTeam::Team01;
	}
	if (Team2Reinforcements > Team1Reinforcements)
	{
		Leader = EFactionsTeam::Team02;
	}

	if (LeadingTeam != Leader)
	{
		OnTeamLeadershipUpdated.Broadcast(Leader);
		LeadingTeam = Leader;
	}
	
}
