// Developed by the Factions community


#include "Factions/PlayerStates/MatchPlayerState.h"
#include "Factions/GameStates/MatchGameState.h"

#include "Net/UnrealNetwork.h"

AMatchPlayerState::AMatchPlayerState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	bIsDead(true)
{
	// Inventory component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	InventoryComponent->SetIsReplicated(true);

	Points = 0;
	Downs = 0;
	Executions = 0;
	Deaths = 0;
}

void AMatchPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(AMatchPlayerState, PlayerMatchState);
	DOREPLIFETIME(AMatchPlayerState, bIsDead);
	DOREPLIFETIME(AMatchPlayerState, Points);
	DOREPLIFETIME(AMatchPlayerState, Downs);
	DOREPLIFETIME(AMatchPlayerState, Executions);
	DOREPLIFETIME(AMatchPlayerState, Deaths);
	
}

void AMatchPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() <= NM_ListenServer)
	{
		InventoryComponent->SetupInventory();
	}

	OnRep_PlayerMatchState();
	OnRep_IsDead();
}

void AMatchPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

bool AMatchPlayerState::IsEntityDead() const
{
	return bIsDead;
}

void AMatchPlayerState::SetPlayerMatchState(const EPlayerMatchState NewValue)
{
	if (GetNetMode() < NM_Client)
	{
		PlayerMatchState = NewValue;
		OnRep_PlayerMatchState();
		ForceNetUpdate();
	}
}

void AMatchPlayerState::SetIsDead(const bool bNewValue)
{
	if (GetNetMode() < NM_Client)
	{
		bIsDead = bNewValue;
		OnRep_IsDead();
		ForceNetUpdate();

		if (bIsDead)
		{
			SetPlayerMatchState(EPlayerMatchState::Spectating);
		}
	}
}

void AMatchPlayerState::AddReward(const ERewardAction RewardAction)
{
	int32 Reward = GetWorld()->GetGameState<AMatchGameState>()->GetRewardActionPoints(RewardAction);

	if (Reward > 0)
	{
		Points += Reward;
		OnRep_Points();
		ForceNetUpdate();

		Client_SendRewardNotification(RewardAction);
	}
}

void AMatchPlayerState::AddDown()
{
	Downs++;
	OnRep_Downs();
	ForceNetUpdate();
}

void AMatchPlayerState::AddExecution()
{
	Executions++;
	OnRep_Executions();
	ForceNetUpdate();
}

void AMatchPlayerState::AddDeath()
{
	Deaths++;
	OnRep_Deaths();
	ForceNetUpdate();
}

void AMatchPlayerState::OnRep_IsDead()
{
	OnPlayerDeadUpdated.Broadcast(bIsDead);
}

void AMatchPlayerState::OnRep_Points()
{
	OnPlayerPointsUpdated.Broadcast(Points);
}

void AMatchPlayerState::OnRep_Downs()
{
	OnPlayerDownsUpdated.Broadcast(Downs);
}

void AMatchPlayerState::OnRep_Executions()
{
	OnPlayerExecutionsUpdated.Broadcast(Executions);
}

void AMatchPlayerState::OnRep_Deaths()
{
	OnPlayerDeathsUpdated.Broadcast(Deaths);
}

void AMatchPlayerState::OnRep_PlayerMatchState()
{
	OnPlayerMatchStateUpdated.Broadcast(PlayerMatchState);
}

void AMatchPlayerState::Client_SendRewardNotification_Implementation(const ERewardAction RewardAction)
{
	int32 Reward = GetWorld()->GetGameState<AMatchGameState>()->GetRewardActionPoints(RewardAction);
	OnRewardNotification.Broadcast(RewardAction, Reward);
}
