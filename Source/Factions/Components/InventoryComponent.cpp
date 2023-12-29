// Developed by the Factions community


#include "Factions/Components/InventoryComponent.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(UInventoryComponent, Selection);

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SetSelection(const int32 NewValue)
{
	if (NewValue != Selection)
	{
		Server_SetSelection(NewValue);
	}

	if (!GetOwner()->HasAuthority())
	{
		Selection = NewValue;
	}
	OnRep_Selection();
	
}

void UInventoryComponent::OffsetVerticalSelection(const int32 Offset)
{
	const int32 NewSelection = FMath::Clamp<int32>(Selection + Offset, 5, 8);
	SetSelection(NewSelection);
}

void UInventoryComponent::OffsetHorizontalSelection(const int32 Offset)
{

}

int32 UInventoryComponent::GetSelection() const
{
	return Selection;
}

void UInventoryComponent::OnRep_Selection()
{
	OnSelectionUpdated.Broadcast(Selection);
}

void UInventoryComponent::Server_SetSelection_Implementation(const int32 NewValue)
{
	Selection = NewValue;
}

bool UInventoryComponent::Server_SetSelection_Validate(const int32 NewValue)
{
	// TODO: Implement RPC validation
	return true;
}

