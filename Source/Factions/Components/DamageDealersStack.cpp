// Developed by the Factions community


#include "Factions/Components/DamageDealersStack.h"
#include "DamageDealersStack.h"

// Sets default values for this component's properties
UDamageDealersStack::UDamageDealersStack()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDamageDealersStack::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDamageDealersStack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageDealersStack::ClearStack()
{
	MainActor = nullptr;
	AssistActor = nullptr;
}

void UDamageDealersStack::PushActor(AActor* Actor)
{
	if (MainActor != Actor)
	{
		AssistActor = MainActor;
		MainActor = Actor;
	}
}

AActor* UDamageDealersStack::GetMainActor() const
{
	return MainActor;
}

AActor* UDamageDealersStack::GetAssistActor() const
{
	return AssistActor;
}

