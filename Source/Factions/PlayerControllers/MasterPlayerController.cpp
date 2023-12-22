// Developed by the Factions community


#include "Factions/PlayerControllers/MasterPlayerController.h"

#include "GameFramework/PlayerState.h"

EFactionsTeam AMasterPlayerController::GetEntityTeam()
{
	IFactionsEntityInterface* Interface = Cast<IFactionsEntityInterface>(GetPlayerState<APlayerState>());
	if (Interface)
	{
		return Interface->GetEntityTeam();
	}
	return EFactionsTeam::None;
}
