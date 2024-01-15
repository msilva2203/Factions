// Developed by the Factions community


#include "Factions/BaseActors/PlayerSpawner.h"
#include "Factions/Pawns/MasterCharacter.h"

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
	FActorSpawnParameters SpawnParameters;
	auto NewCharacter = GetWorld()->SpawnActor<AMasterCharacter>(GetActorLocation(), GetActorRotation(), SpawnParameters);
	Player->Possess(NewCharacter);

	bIsAvailable = false;
}

bool APlayerSpawner::IsAvailable()
{
	return bIsAvailable;
}

