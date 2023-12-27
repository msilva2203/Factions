// Developed by the Factions community


#include "Factions/GameStates/LobbyGameState.h"

#include "net/UnrealNetwork.h"

ALobbyGameState::ALobbyGameState()
{
	NetDormancy = ENetDormancy::DORM_DormantAll;
	NetUpdateFrequency = 0.0f;
}

void ALobbyGameState::BeginPlay()
{
	Super::BeginPlay();

}

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
		if (LobbyGameMode != NewGameMode)
		{
			LobbyGameMode = NewGameMode;
			OnRep_LobbyGameMode();
			ForceNetUpdate();
		}
	}
}

void ALobbyGameState::OnRep_LobbyGameMode()
{
	if (FactionsSessionSubsystem)
	{
		FactionsSessionSubsystem->SetSessionGameMode(LobbyGameMode);
	}
}
