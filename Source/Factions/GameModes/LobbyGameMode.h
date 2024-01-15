// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameModes/MasterGameMode.h"
#include "Factions/Data/GameModeData.h"

#include "LobbyGameMode.generated.h"

//Forward declarations
class ALobbyGameState;

/**
 * 
 */
UCLASS()
class FACTIONS_API ALobbyGameMode : public AMasterGameMode
{
	GENERATED_BODY()
	
public:
	ALobbyGameMode(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Lobby Game Mode")
	void StartMatch();

	UPROPERTY(BlueprintReadOnly, Category = "Lobby Game Mode")
	ALobbyGameState* LobbyGameState;

public:
	UFUNCTION(Exec, Category = "Lobby Game Mode")
	void gm_lobby_change_gamemode(const EFactionsGameMode NewGameMode);
};
