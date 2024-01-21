// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameModes/MasterGameMode.h"
#include "Factions/BaseActors/PlayerSpawner.h"

#include "MatchGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AMatchGameMode : public AMasterGameMode
{
	GENERATED_BODY()
	
public:
	AMatchGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Start() override;

	UFUNCTION()
	virtual void StartPlayers();

	UFUNCTION()
	virtual bool CanPlayerRespawn(AMasterPlayerController* Player) const;

	UFUNCTION()
	virtual void RespawnPlayer(AMasterPlayerController* Player);

	UFUNCTION()
	virtual APlayerSpawner* FindPlayerSpawner(AMasterPlayerController* Player);

	UFUNCTION()
	virtual void AssignTeamToPlayer(AMasterPlayerState* Player);

	UFUNCTION()
	virtual void OnGameTimeUpdate(int32 Time);

	virtual void PlayerPostLogin(AMasterPlayerController* PlayerController) override;
	virtual void PlayerLogout(AMasterPlayerController* PlayerController) override;

	UPROPERTY(BlueprintReadOnly, Category = "Match Game Mode")
	TArray<APlayerSpawner*> StartSpawners;

	UPROPERTY(BlueprintReadOnly, Category = "Match Game Mode")
	TArray<APlayerSpawner*> PlayerSpawners;

public:
	UFUNCTION(Exec, Category = "Supply Raid")
	void gm_update_timeremaining(const int32 Time);
};
