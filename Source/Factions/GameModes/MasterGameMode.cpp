// Developed by the Factions community


#include "Factions/GameModes/MasterGameMode.h"

#include "Factions/GameStates/MasterGameState.h"
#include "Factions/PlayerControllers/MasterPlayerController.h"
#include "Factions/PlayerStates/MasterPlayerState.h"

AMasterGameMode::AMasterGameMode() :
	Super()
{
	GameStateClass = AMasterGameState::StaticClass();
	PlayerControllerClass = AMasterPlayerController::StaticClass();
	PlayerStateClass = AMasterPlayerState::StaticClass();

	DefaultPlayerName = FText::FromName(TEXT("FACTIONS PLAYER"));
}

void AMasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Chaches a reference to the factions session subsytem
	FactionsSessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();

}

void AMasterGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::OnPostLogin(PlayerController);

	if (auto Player = Cast<AMasterPlayerController>(PlayerController))
	{
		ConnectedPlayers.Add(Player);
		PlayerPostLogin(Player);
	}
}

void AMasterGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
	Super::HandleStartingNewPlayer_Implementation(PlayerController);

}

void AMasterGameMode::Logout(AController* Controller)
{
	Super::Logout(Controller);

	if (auto Player = Cast<AMasterPlayerController>(Controller))
	{
		ConnectedPlayers.Remove(Player);
		PlayerLogout(Player);
	}
}

void AMasterGameMode::PlayerPostLogin(AMasterPlayerController* PlayerController)
{
	if (FactionsSessionSubsystem)
	{
		if (auto PlayerState = PlayerController->GetPlayerState<AMasterPlayerState>())
		{
			FSessionPlayerData SessionPlayerData;
			if (FactionsSessionSubsystem->GetSessionPlayerData(PlayerState, SessionPlayerData))
			{
				PlayerState->SetPlayerTeam(SessionPlayerData.Team);
			}
		}
	}
	
}

void AMasterGameMode::PlayerLogout(AMasterPlayerController* PlayerController)
{

}


