// Developed by the Factions community


#include "Factions/GameStates/MasterGameState.h"

AMasterGameState::AMasterGameState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	NetDormancy = ENetDormancy::DORM_DormantAll;
	NetUpdateFrequency = 0.0f;
}

void AMasterGameState::BeginPlay()
{
	Super::BeginPlay();

	FactionsSessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();
}
