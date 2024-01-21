/// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerStates/MasterPlayerState.h"

#include "LobbyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ALobbyPlayerState : public AMasterPlayerState
{
	GENERATED_BODY()
	
public:
	ALobbyPlayerState(const FObjectInitializer& ObjectInitializer);
};
