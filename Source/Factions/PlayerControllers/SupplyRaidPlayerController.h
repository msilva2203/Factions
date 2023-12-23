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

	UFUNCTION(Exec, Category = "Supply Raid")
	void update_team1reinforcements(const int32 NewValue);

	UFUNCTION(Exec, Category = "Supply Raid")
	void update_team2reinforcements(const int32 NewValue);
};
