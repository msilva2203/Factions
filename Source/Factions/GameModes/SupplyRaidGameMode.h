// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameModes/MasterGameMode.h"
#include "Factions/GameStates/SupplyRaidGameState.h"

#include "SupplyRaidGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ASupplyRaidGameMode : public AMasterGameMode
{
	GENERATED_BODY()

	ASupplyRaidGameMode();
	
public:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Supply Raid")
	ASupplyRaidGameState* SupplyRaidGameState;
};
