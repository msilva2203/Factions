// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "Factions/Subsystems/FactionsSessionSubsystem.h"

#include "MasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AMasterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMasterGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Match Game Mode")
	void OnStart();

	UFUNCTION()
	virtual void Start();

	virtual void PostLogin(APlayerController* PlayerController) override;
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* PlayerController) override;
	virtual void Logout(AController* Controller) override;

	UFUNCTION()
	virtual void PlayerPostLogin(AMasterPlayerController* PlayerController);

	UFUNCTION()
	virtual void PlayerLogout(AMasterPlayerController* PlayerController);

	UFUNCTION()
	int32 GetTeamSize(const EFactionsTeam Team);

	UFUNCTION(Exec, Category = "Master Game Mode")
	void gm_start();

	UPROPERTY()
	bool bStarted;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Master Game Mode")
	UFactionsSessionSubsystem* FactionsSessionSubsystem;

	UPROPERTY(BlueprintReadOnly, Category = "Master Game Mode")
	TArray<AMasterPlayerController*> ConnectedPlayers;

};
