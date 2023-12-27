// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameStates/MasterGameState.h"
#include "Factions/Data/GameModeData.h"

#include "LobbyGameState.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API ALobbyGameState : public AMasterGameState
{
	GENERATED_BODY()
	
public:
	ALobbyGameState();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, Category = "Lobby Game State")
	void ChangeGameMode(const EFactionsGameMode NewGameMode);

	UPROPERTY(ReplicatedUsing = OnRep_LobbyGameMode, BlueprintReadOnly, Category = "Lobby Game State")
	EFactionsGameMode LobbyGameMode;

protected:
	UFUNCTION()
	void OnRep_LobbyGameMode();
};
