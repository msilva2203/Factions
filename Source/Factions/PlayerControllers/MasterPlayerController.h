// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Factions/Interfaces/FactionsEntityInterface.h"

#include "MasterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AMasterPlayerController : public APlayerController, public IFactionsEntityInterface
{
	GENERATED_BODY()
	
public:
	virtual EFactionsTeam GetEntityTeam() override;
};
