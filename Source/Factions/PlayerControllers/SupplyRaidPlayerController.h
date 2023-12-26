// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerControllers/MasterPlayerController.h"

#include "SupplyRaidPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ASupplyRaidPlayerController : public AMasterPlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

};
