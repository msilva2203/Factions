// Developed by the Factions community


#include "Factions/Components/EntityAttributeComponent.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
UEntityAttributeComponent::UEntityAttributeComponent() : 
	DefaultAttributeValue(100.0f),
	MinValue(0.0f),
	MaxValue(DefaultAttributeValue)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	AttributeValue = DefaultAttributeValue;
}


// Called when the game starts
void UEntityAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//if (GetOwner()->HasAuthority())
	//{
	//	SetAttributeValue(DefaultAttributeValue);
	//}
}

void UEntityAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(UEntityAttributeComponent, AttributeValue);
}


// Called every frame
void UEntityAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEntityAttributeComponent::SetAttributeValue(const float NewValue)
{
	AttributeValue = FMath::Clamp<float>(NewValue, MinValue, MaxValue);
	OnRep_AttributeValue();
}

void UEntityAttributeComponent::OffsetAttributeValue(const float Offset)
{
	SetAttributeValue(AttributeValue + Offset);
}

float UEntityAttributeComponent::GetAttributeValue() const
{
	return AttributeValue;
}

float UEntityAttributeComponent::GetPercent() const
{
	return AttributeValue / DefaultAttributeValue;
}

void UEntityAttributeComponent::OnRep_AttributeValue()
{
	OnAttributeUpdated.Broadcast(AttributeValue, GetPercent());
}
