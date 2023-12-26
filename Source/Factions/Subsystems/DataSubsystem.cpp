// Developed by the Factions community


#include "Factions/Subsystems/DataSubsystem.h"

void UDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UDataSubsystem::PushGameModeData(TArray<UGameModeData*> NewData)
{
	FactionsGameModeData = NewData;
}

UGameModeData* UDataSubsystem::GetGameModeData(const EFactionsGameMode GameMode)
{
	for (auto GMData : FactionsGameModeData)
	{
		if (GMData->Data.GameMode == GameMode)
		{
			return GMData;
		}
	}
	return nullptr;
}
