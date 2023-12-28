// Developed by the Factions community


#include "Factions/Subsystems/SettingsSubsystem.h"

void USettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	FOV = 90.0f;
	SensitivityX = 1.0f;
	SensitivityY = 1.0f;
	SensitivityAimingX = 1.0f;
	SensitivityAimingY = 1.0f;
}
