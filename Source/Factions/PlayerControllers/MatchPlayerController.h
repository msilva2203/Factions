// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerControllers/MasterPlayerController.h"
#include "Factions/BaseActors/ArenaCamera.h"
#include "Factions/PlayerStates/MatchPlayerState.h"
#include "Factions/Widgets/BaseScoreboard.h"

#include "MatchPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateReplicatedDelegate, AMatchPlayerState*, PlayerState);

/**
 * 
 */
UCLASS()
class FACTIONS_API AMatchPlayerController : public AMasterPlayerController
{
	GENERATED_BODY()

public:
	AMatchPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual bool IsEntityDead() const override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;
	virtual void SetupPlayerController() override;

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION(BlueprintPure, Category = "Match Player Controller")
	bool IsSpectating() const;

	UFUNCTION(BlueprintCallable, Category = "Match Player Controller")
	void SpectateCamera(AArenaCamera* Camera);

	UFUNCTION(BlueprintImplementableEvent, Category = "Match Player Controller")
	void OnPlayerMatchStateUpdated(const EPlayerMatchState NewValue);

	UFUNCTION()
	virtual void PlayerMatchStateUpdated(const EPlayerMatchState NewValue);

	UPROPERTY(BlueprintReadOnly, Category = "Match Player Controller")
	EPlayerMatchState PlayerMatchState;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating")
	TArray<AArenaCamera*> ArenaCameras;

	UPROPERTY(BlueprintReadOnly, Category = "Spectating")
	int32 SpectatingCameraIndex;

	UPROPERTY()
	APawn* PreviousPawn;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnPlayerStateReplicatedDelegate OnPlayerStateReplicated;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UBaseScoreboard> ScoreboardClass;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UBaseHUD> GameModeHUDClass;

	UPROPERTY(EditAnywhere, Category = "HUD")
	TSubclassOf<UBaseHUD> MainHUDClass;

	UFUNCTION(Exec, Category = "Master Player Controller")
	void player_set_material(EMaterial Material, int32 NewValue);

protected:
	UFUNCTION()
	virtual void InputSpectateCamera();

	UFUNCTION()
	virtual void InputSpectatePlayer();

	UFUNCTION()
	virtual void InputShowScoreboard();
};
