// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerControllers/MatchPlayerController.h"

#include "SupplyRaidPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ASupplyRaidPlayerController : public AMatchPlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

};
