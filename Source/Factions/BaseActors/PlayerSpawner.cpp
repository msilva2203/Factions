// Developed by the Factions community


#include "Factions/BaseActors/PlayerSpawner.h"

// Sets default values
APlayerSpawner::APlayerSpawner() :
	SpawnerTeam(EFactionsTeam::None),
	bIsStartSpawner(false),
	bIsAvailable(true)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

EFactionsTeam APlayerSpawner::GetEntityTeam()
{
	return SpawnerTeam;
}

void APlayerSpawner::SpawnPlayer(AMasterPlayerController* Player)
{
	Player->UnPossess();

	// Spawning the character
	FActorSpawnParameters SpawnParameters;
	ESpawnActorCollisionHandlingMethod SpawnCollisionMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	auto NewCharacter = GetWorld()->SpawnActorDeferred<AMasterCharacter>(CharacterSubclass, GetActorTransform(), Player, nullptr, SpawnCollisionMethod);

	// Setup character properties and possession
	Player->Possess(NewCharacter);

	// Finish spawning
	NewCharacter->FinishSpawning(GetActorTransform());

	bIsAvailable = false;
}

bool APlayerSpawner::IsAvailable()
{
	return bIsAvailable;
}

