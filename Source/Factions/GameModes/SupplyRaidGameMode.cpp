// Developed by the Factions community


#include "Factions/GameModes/SupplyRaidGameMode.h"

#include "Factions/PlayerControllers/SupplyRaidPlayerController.h"
#include "Factions/PlayerStates/MatchPlayerState.h"

ASupplyRaidGameMode::ASupplyRaidGameMode() :
	Super()
{
	GameStateClass = ASupplyRaidGameState::StaticClass();
	PlayerStateClass = AMatchPlayerState::StaticClass();
	PlayerControllerClass = ASupplyRaidPlayerController::StaticClass();
}

void ASupplyRaidGameMode::BeginPlay()
{
	Super::BeginPlay();

	SupplyRaidGameState = Cast<ASupplyRaidGameState>(GameState);
}

void ASupplyRaidGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);

}

//void ASupplyRaidGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
//{
//	Super::HandleStartingNewPlayer_Implementation(PlayerController);
//
//}

void ASupplyRaidGameMode::Logout(AController* Controller)
{
	Super::Logout(Controller);

}

void ASupplyRaidGameMode::PlayerPostLogin(AMasterPlayerController* Player)
{
	Super::PlayerPostLogin(Player);

}

void ASupplyRaidGameMode::PlayerLogout(AMasterPlayerController* Player)
{
	Super::PlayerLogout(Player);

}

void ASupplyRaidGameMode::gm_sr_update_team1reinforcements(const int32 NewValue)
{
	SupplyRaidGameState->SetTeamReinforcements(EFactionsTeam::Team01, NewValue);
}

void ASupplyRaidGameMode::gm_sr_update_team2reinforcements(const int32 NewValue)
{
	SupplyRaidGameState->SetTeamReinforcements(EFactionsTeam::Team02, NewValue);
}

void ASupplyRaidGameMode::gm_sr_update_timeremaining(const int32 Time)
{
	SupplyRaidGameState->SetRemainingTime(Time, true);
}
