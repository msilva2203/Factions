// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerControllers/MasterPlayerController.h"
#include "Factions/BaseActors/ArenaCamera.h"
#include "Factions/PlayerStates/MatchPlayerState.h"

#include "MatchPlayerController.generated.h"

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

protected:
	UFUNCTION()
	virtual void InputSpectateCamera();

	UFUNCTION()
	virtual void InputSpectatePlayer();
};
