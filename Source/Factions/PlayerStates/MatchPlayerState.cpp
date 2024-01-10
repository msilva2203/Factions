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
