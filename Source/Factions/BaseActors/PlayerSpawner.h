// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Factions/Factions.h"
#include "Factions/PlayerControllers/MasterPlayerController.h"
#include "Factions/Pawns/MasterCharacter.h"

#include "PlayerSpawner.generated.h"

UCLASS()
class FACTIONS_API APlayerSpawner : public AActor, public IFactionsEntityInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual EFactionsTeam GetEntityTeam() override;

	UFUNCTION()
	void SpawnPlayer(AMasterPlayerController* Player);

	UFUNCTION(BlueprintPure, Category = "Player Spawner")
	bool IsAvailable();

	UPROPERTY(EditAnywhere, Category = "Player Spawner")
	TSubclassOf<AMasterCharacter> CharacterSubclass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Spawner")
	EFactionsTeam SpawnerTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Spawner")
	bool bIsStartSpawner;

	UPROPERTY()
	bool bIsAvailable;
};
