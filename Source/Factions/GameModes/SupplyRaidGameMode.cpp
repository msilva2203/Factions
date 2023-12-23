// Developed by the Factions community


#include "Factions/GameModes/SupplyRaidGameMode.h"

#include "Factions/PlayerStates/MasterPlayerState.h"
#include "Factions/PlayerControllers/SupplyRaidPlayerController.h"

ASupplyRaidGameMode::ASupplyRaidGameMode()
{
	GameStateClass = ASupplyRaidGameState::StaticClass();
	PlayerStateClass = AMasterPlayerState::StaticClass();
	PlayerControllerClass = ASupplyRaidPlayerController::StaticClass();
}

void ASupplyRaidGameMode::BeginPlay()
{
	Super::BeginPlay();

	SupplyRaidGameState = Cast<ASupplyRaidGameState>(GameState);
}
