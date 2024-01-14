// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameModes/MatchGameMode.h"
#include "Factions/GameStates/SupplyRaidGameState.h"

#include "SupplyRaidGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ASupplyRaidGameMode : public AMatchGameMode
{
	GENERATED_BODY()

public:
	ASupplyRaidGameMode();

	virtual void BeginPlay() override;

	virtual void PostLogin(APlayerController* PlayerController) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* PlayerController) override;
	virtual void Logout(AController* Controller) override;

	virtual void PlayerPostLogin(AMasterPlayerController* Player) override;
	virtual void PlayerLogout(AMasterPlayerController* Player) override;

	UPROPERTY(BlueprintReadOnly, Category = "Supply Raid")
	ASupplyRaidGameState* SupplyRaidGameState;

public:
	UFUNCTION(Exec, Category = "Supply Raid")
	void gm_sr_update_team1reinforcements(const int32 NewValue);

	UFUNCTION(Exec, Category = "Supply Raid")
	void gm_sr_update_team2reinforcements(const int32 NewValue);

	UFUNCTION(Exec, Category = "Supply Raid")
	void gm_sr_update_timeremaining(const int32 Time);
};
