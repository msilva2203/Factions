// Developed by the Factions community


#include "Factions/PlayerControllers/LobbyPlayerController.h"

#include "Factions/Subsystems/FactionsSessionSubsystem.h"

ALobbyPlayerController::ALobbyPlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
}

void ALobbyPlayerController::Client_RegisterPlayersInLobby_Implementation()
{
	auto FactionsSessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();
	if (FactionsSessionSubsystem)
	{
		FactionsSessionSubsystem->RegisterPlayersInSession();
	}
}
