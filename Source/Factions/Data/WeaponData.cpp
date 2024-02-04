// Developed by the Factions community


#include "Factions/Data/WeaponData.h"

bool UWeaponData::IsFullAuto(int32 Level) const
{
	return GetWeaponLevelData(Level).bIsFullAuto;
}

int32 UWeaponData::GetBurstAmount(int32 Level) const
{
	return GetWeaponLevelData(Level).BurstAmount;
}

float UWeaponData::GetFireRate(int32 Level) const
{
	return GetWeaponLevelData(Level).FireRate;
}

float UWeaponData::GetBurstRate(int32 Level) const
{
	return GetWeaponLevelData(Level).BurstRate;
}

int32 UWeaponData::GetMagSize(int32 Level) const
{
	return GetWeaponLevelData(Level).MagSize;
}

float UWeaponData::GetPrecisionInterpSpeed(int32 Level) const
{
	return GetWeaponLevelData(Level).PrecisionInterpSpeed;
}

const FFactionsWeaponData& UWeaponData::GetWeaponLevelData(int32 Level) const
{
	Level = FMath::Clamp<int32>(Level, 0, 2);
	switch (Level)
	{
	case 0:
		return Level1Data;
	case 1:
		return Level2Data;
	case 2:
		return Level3Data;
	default:
		return Level1Data;
	}
}
