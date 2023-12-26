// Developed by the Factions community


#include "Factions/GameModes/LobbyGameMode.h"

#include "Factions/PlayerStates/LobbyPlayerState.h"
#include "Factions/GameStates/LobbyGameState.h"
#include "Factions/PlayerControllers/LobbyPlayerController.h"

ALobbyGameMode::ALobbyGameMode() :
	Super()
{
	PlayerStateClass = ALobbyPlayerState::StaticClass();
	GameStateClass = ALobbyGameState::StaticClass();
	PlayerControllerClass = ALobbyPlayerController::StaticClass();

}

void ALobbyGameMode::BeginPlay()
{
	Super::BeginPlay();

	LobbyGameState = Cast<ALobbyGameState>(GameState);
}

void ALobbyGameMode::StartMatch()
{
	// Registers session player immediately for dedicated server
	if (IsRunningDedicatedServer())
	{
		FactionsSessionSubsystem->RegisterPlayersInSession();
	}

	// Registers session players on all connected players, including the host if running on listen server
	for (auto Player : ConnectedPlayers)
	{
		if (auto LobbyPlayer = Cast<ALobbyPlayerController>(Player))
		{
			LobbyPlayer->Client_RegisterPlayersInLobby();
		}
	}
}

void ALobbyGameMode::gm_lobby_change_gamemode(const EFactionsGameMode NewGameMode)
{
	LobbyGameState->ChangeGameMode(NewGameMode);

}
