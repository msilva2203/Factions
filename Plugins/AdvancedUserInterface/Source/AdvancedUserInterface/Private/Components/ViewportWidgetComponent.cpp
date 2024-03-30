// Developed by the Factions community


#include "Components/ViewportWidgetComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UViewportWidgetComponent::UViewportWidgetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UViewportWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UViewportWidgetComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Widget->RemoveFromParent();
}

// Called every frame
void UViewportWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	FVector2D ScreenPosition;
	FVector2D ViewportSize;
	FVector2D DesiredSize;
	auto WorldPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	if (Widget)
	{
		UGameplayStatics::ProjectWorldToScreen(WorldPlayerController, GetComponentLocation(), ScreenPosition, false);
		GEngine->GameViewport->GetViewportSize(ViewportSize);
		DesiredSize = Widget->GetDesiredSize();

		DesiredSize.X /= 2.0f;
		DesiredSize.Y /= 2.0f;

		// Centering the widget
		ScreenPosition.X -= DesiredSize.X / 2.0f;
		ScreenPosition.Y -= DesiredSize.Y / 2.0f;

		ViewportSize -= DesiredSize;

		ScreenPosition.X = FMath::Clamp<float>(ScreenPosition.X, SafeZoneX, ViewportSize.X - SafeZoneX);
		ScreenPosition.Y = FMath::Clamp<float>(ScreenPosition.Y, SafeZoneY, ViewportSize.Y - SafeZoneY);

		Widget->SetPositionInViewport(ScreenPosition, true);
	}
}

void UViewportWidgetComponent::SetWidget(UUserWidget* NewWidget)
{
	if (NewWidget)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}

		Widget = NewWidget;
		Widget->AddToViewport();
	}
}

