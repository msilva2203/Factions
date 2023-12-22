// Developed by the Factions community


#include "Factions/Subsystems/RadarSubsystem.h"

void URadarSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	this->DisplayRadius = 275.0f / 2.0f;
	this->PhysicalRadius = 50.0f;
}

void URadarSubsystem::UpdateCenterTransform(FRadarTransform NewTransform)
{
	CenterTransform = NewTransform;
	OnRadarCenterTransformUpdate.Broadcast(CenterTransform);
}

void URadarSubsystem::SetPhysicalRadius(const float NewRadius)
{
	this->PhysicalRadius = NewRadius;
}

void URadarSubsystem::SetDisplayRadius(const float NewRadius)
{
	this->DisplayRadius = NewRadius;
}

void URadarSubsystem::AddRadarIcon(UBaseRadarIcon* RadarIcon)
{
	RadarIcons.Add(RadarIcon);
	OnRadarIconPushed.Broadcast(RadarIcon);
}

void URadarSubsystem::RemoveRadarIcon(UBaseRadarIcon* RadarIcon)
{
	RadarIcons.Remove(RadarIcon);
	OnRadarIconRemoved.Broadcast(RadarIcon);
}
