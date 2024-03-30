// Developed by the Factions community


#include "Factions/GameStates/MatchGameState.h"
#include "Net/UnrealNetwork.h"

#define DEFAULT_REMAINING_TIME 1200

AMatchGameState::AMatchGameState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	RemainingTime(DEFAULT_REMAINING_TIME)
{
}

void AMatchGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AMatchGameState, RemainingTime, COND_InitialOnly);
	DOREPLIFETIME(AMatchGameState, bInProgress);
}

void AMatchGameState::BeginPlay()
{
	Super::BeginPlay();
}

void AMatchGameState::SetRemainingTime(const int32 Time, const bool bForce)
{
	if (GetWorld()->GetNetMode() < ENetMode::NM_Client)
	{
		RemainingTime = Time;
		OnRep_RemainingTime();
		ForceNetUpdate();

		if (bForce)
		{
			NetMulticast_SetRemainingTime(RemainingTime);
		}
	}
}

int32 AMatchGameState::GetRewardActionPoints(const ERewardAction RewardAction)
{
	switch (RewardAction)
	{
	case ERewardAction::Down:
		return Reward_Down;
	case ERewardAction::Execution:
		return Reward_Execution;
	case ERewardAction::SpecExecution:
		return Reward_SpecExecution;
	case ERewardAction::Assist:
		return Reward_Assist;
	case ERewardAction::Revive:
		return Reward_Revive;
	case ERewardAction::None:
	default:
		return 0;
	}
}

void AMatchGameState::SetInProgress(const bool bNewValue)
{
	if (GetWorld()->GetNetMode() < ENetMode::NM_Client)
	{
		bInProgress = bNewValue;
		OnRep_InProgress();
		ForceNetUpdate();
	}
}

void AMatchGameState::OnRep_RemainingTime()
{
	OnGameTimeUpdate.Broadcast(RemainingTime);
}

void AMatchGameState::OnRep_InProgress()
{
	if (bInProgress)
	{
		GetWorld()->GetTimerManager().SetTimer(GameTimer, this, &AMatchGameState::OnGameTimerUpdate, 1.0f, true, 1.0f);
	}
	else
	{
		GetWorld()->GetTimerManager().ClearTimer(GameTimer);
	}
}

void AMatchGameState::OnGameTimerUpdate()
{
	RemainingTime--;
	OnRep_RemainingTime();
}

void AMatchGameState::NetMulticast_SetRemainingTime_Implementation(const int32 Time)
{
	RemainingTime = Time;
	OnRep_RemainingTime();

	// Synchronizes timer
	OnRep_InProgress();
}
