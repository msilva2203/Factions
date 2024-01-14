// Developed by the Factions community


#include "Factions/BaseActors/ArenaCamera.h"

// Sets default values
AArenaCamera::AArenaCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

}

// Called when the game starts or when spawned
void AArenaCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArenaCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArenaCamera::Spectate(APlayerController* Player)
{
	Player->SetViewTarget(this);
}

