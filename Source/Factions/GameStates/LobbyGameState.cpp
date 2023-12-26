// Developed by the Factions community


#include "Factions/GameStates/LobbyGameState.h"

#include "net/UnrealNetwork.h"

void ALobbyGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(ALobbyGameState, LobbyGameMode);
}

void ALobbyGameState::ChangeGameMode(const EFactionsGameMode NewGameMode)
{
	if (GetNetMode() < NM_Client)
	{
		LobbyGameMode = NewGameMode;
		OnRep_LobbyGameMode();
	}
}

void ALobbyGameState::OnRep_LobbyGameMode()
{
	OnLobbyGameModeUpdated.Broadcast(LobbyGameMode);
}
