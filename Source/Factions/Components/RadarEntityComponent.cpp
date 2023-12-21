// Developed by the Factions community


#include "Factions/Components/RadarEntityComponent.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

// Sets default values for this component's properties
URadarEntityComponent::URadarEntityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URadarEntityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	auto Player = GetWorld()->GetFirstPlayerController();
	RadarSubsystem = Player->GetLocalPlayer()->GetSubsystem<URadarSubsystem>();
	
}


// Called every frame
void URadarEntityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void URadarEntityComponent::PushEntity()
{
	auto IconOwner = GetWorld()->GetFirstPlayerController();
	Icon = CreateWidget<UBaseRadarIcon>(IconOwner, RadarIconSubclass);

	if (Icon)
	{
		RadarSubsystem->OnRadarIconPushed.Broadcast(Icon);
	}
}

void URadarEntityComponent::RemoveEntity()
{
	if (Icon)
	{
		RadarSubsystem->OnRadarIconRemoved.Broadcast(Icon);
	}
}

void URadarEntityComponent::UpdateIconTransform(FRadarTransform IconTransform)
{
	if (Icon)
	{
		const float PhysicalRadius = RadarSubsystem->PhysicalRadius;
		const float DisplayRadius = RadarSubsystem->DisplayRadius;
		const auto Center = RadarSubsystem->CenterTransform;

		FVector2D RelativePosition;
		RelativePosition.X = (IconTransform.Translation.X - Center.Translation.X) / PhysicalRadius * DisplayRadius;
		RelativePosition.Y = (IconTransform.Translation.Y - Center.Translation.Y) / PhysicalRadius * DisplayRadius;

		auto Slot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Icon);

		if (Slot)
		{
			FVector2D Normalized = RelativePosition;
			Normalized.Normalize();

			float Length = RelativePosition.Length();
			Length = FMath::Clamp<float>(Length, 0.0f, DisplayRadius);

			Normalized = Normalized * Length;
			Slot->SetPosition(Normalized);
		}
	}
}

