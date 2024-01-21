// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerControllers/MasterPlayerController.h"

#include "LobbyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ALobbyPlayerController : public AMasterPlayerController
{
	GENERATED_BODY()
	
public:
	ALobbyPlayerController(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Client, Reliable, Category = "Lobby Player Controller")
	void Client_RegisterPlayersInLobby();
	void Client_RegisterPlayersInLobby_Implementation();
};
