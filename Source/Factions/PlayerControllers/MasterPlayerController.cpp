// Developed by the Factions community


#include "Factions/PlayerControllers/MasterPlayerController.h"

#include "GameFramework/PlayerState.h"
#include "Factions/PlayerStates/MasterPlayerState.h"

void AMasterPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

EFactionsTeam AMasterPlayerController::GetEntityTeam()
{
	IFactionsEntityInterface* Interface = Cast<IFactionsEntityInterface>(GetPlayerState<APlayerState>());
	if (Interface)
	{
		return Interface->GetEntityTeam();
	}
	return EFactionsTeam::None;
}

void AMasterPlayerController::Client_SetPlayerTeam_Implementation(const EFactionsTeam NewTeam)
{
	Server_SetPlayerTeam(NewTeam);
}

void AMasterPlayerController::Server_SetPlayerTeam_Implementation(const EFactionsTeam NewTeam)
{
	GetPlayerState<AMasterPlayerState>()->SetPlayerTeam(NewTeam);
}
