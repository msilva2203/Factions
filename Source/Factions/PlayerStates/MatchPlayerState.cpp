// Developed by the Factions community


#include "Factions/PlayerStates/MatchPlayerState.h"

#include "Net/UnrealNetwork.h"

AMatchPlayerState::AMatchPlayerState()
{
	// Inventory component
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	InventoryComponent->SetIsReplicated(true);
}

void AMatchPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(AMatchPlayerState, PlayerMatchState);
	DOREPLIFETIME(AMatchPlayerState, bIsDead);
	
}

void AMatchPlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (GetNetMode() <= NM_ListenServer)
	{
		InventoryComponent->SetupInventory();
	}
}

void AMatchPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

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
	}
}

void AMatchPlayerState::OnRep_IsDead()
{

}

void AMatchPlayerState::OnRep_PlayerMatchState()
{
	OnPlayerMatchStateUpdated.Broadcast(PlayerMatchState);
}
