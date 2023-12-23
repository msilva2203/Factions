// Developed by the Factions community


#include "Factions/PlayerControllers/SupplyRaidPlayerController.h"

#include "Factions/GameStates/SupplyRaidGameState.h"

void ASupplyRaidPlayerController::BeginPlay()
{
	Super::BeginPlay();


}

void ASupplyRaidPlayerController::update_team1reinforcements(const int32 NewValue)
{
	if (auto GameState = Cast<ASupplyRaidGameState>(GetWorld()->GetGameState()))
	{
		GameState->SetTeamReinforcements(EFactionsTeam::Team01, NewValue);
	}

}

void ASupplyRaidPlayerController::update_team2reinforcements(const int32 NewValue)
{
	if (auto GameState = Cast<ASupplyRaidGameState>(GetWorld()->GetGameState()))
	{
		GameState->SetTeamReinforcements(EFactionsTeam::Team02, NewValue);
	}
}

