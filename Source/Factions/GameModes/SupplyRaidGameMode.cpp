// Developed by the Factions community


#include "Factions/GameModes/SupplyRaidGameMode.h"

#include "Factions/PlayerControllers/SupplyRaidPlayerController.h"
#include "Factions/PlayerStates/MatchPlayerState.h"

ASupplyRaidGameMode::ASupplyRaidGameMode(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	GameStateClass = ASupplyRaidGameState::StaticClass();
	PlayerStateClass = AMatchPlayerState::StaticClass();
	PlayerControllerClass = ASupplyRaidPlayerController::StaticClass();
}

void ASupplyRaidGameMode::BeginPlay()
{
	Super::BeginPlay();

	SupplyRaidGameState = Cast<ASupplyRaidGameState>(GameState);

	// Default match rules
	SupplyRaidGameState->SetRemainingTime(1200, true);
	SupplyRaidGameState->SetTeamReinforcements(EFactionsTeam::Team01, 20);
	SupplyRaidGameState->SetTeamReinforcements(EFactionsTeam::Team02, 20);
}

void ASupplyRaidGameMode::Start()
{
	Super::Start();
}

bool ASupplyRaidGameMode::CanPlayerRespawn(AMasterPlayerController* Player) const
{
	Super::CanPlayerRespawn(Player);

	const auto PlayerTeam = FactionsSessionSubsystem->GetEntityTeam(Player);
	const int32 TeamReinforcements = SupplyRaidGameState->GetTeamReinforcements(PlayerTeam);
	return TeamReinforcements > 0;
}

void ASupplyRaidGameMode::RespawnPlayer(AMasterPlayerController* Player)
{
	Super::RespawnPlayer(Player);

	const auto PlayerTeam = FactionsSessionSubsystem->GetEntityTeam(Player);
	const int32 TeamReinforcements = SupplyRaidGameState->GetTeamReinforcements(PlayerTeam);
	SupplyRaidGameState->SetTeamReinforcements(PlayerTeam, TeamReinforcements - 1);
}

void ASupplyRaidGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::PostLogin(PlayerController);

}

void ASupplyRaidGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
	Super::HandleStartingNewPlayer_Implementation(PlayerController);

}

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
