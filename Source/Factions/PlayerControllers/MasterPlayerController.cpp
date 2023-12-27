// Developed by the Factions community


#include "Factions/PlayerControllers/MasterPlayerController.h"

#include "GameFramework/PlayerState.h"
#include "Factions/PlayerStates/MasterPlayerState.h"

AMasterPlayerController::AMasterPlayerController()
{
	NetDormancy = ENetDormancy::DORM_DormantAll;
	NetUpdateFrequency = 0.0f;
}

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

void AMasterPlayerController::Server_SetPlayerTeam_Implementation(const EFactionsTeam NewTeam)
{
	GetPlayerState<AMasterPlayerState>()->SetPlayerTeam(NewTeam);
}

bool AMasterPlayerController::Server_SetPlayerTeam_Validate(const EFactionsTeam NewTeam)
{
	// Implement RPC validation
	return true;
}
