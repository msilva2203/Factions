// Developed by the Factions community


#include "Factions/Components/InventoryComponent.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"


#define SLOT_EXPLOSIVE_BOMB 5
#define SLOT_HEALTH_KIT	6
#define SLOT_FIRE_BOMB 7
#define SLOT_SUPPORT_BOMB 8
#define SLOT_SHORT_WEAPON 2
#define SLOT_LARGE_WEAPON 1


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(UInventoryComponent, Selection);
	DOREPLIFETIME(UInventoryComponent, HealthKit);
	DOREPLIFETIME(UInventoryComponent, ExplosiveBomb);
	DOREPLIFETIME(UInventoryComponent, FireBomb);
	DOREPLIFETIME(UInventoryComponent, SupportBomb);
	DOREPLIFETIME(UInventoryComponent, ShortWeapon);
	DOREPLIFETIME(UInventoryComponent, LargeWeapon);

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
	// bCanEverTick is set to false.
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::SetupInventory()
{
	if (GetOwner()->HasAuthority())
	{
		// Gets a reference to the NET owner of the inventory
		AActor* EquipmentOwner = Cast<APlayerState>(GetOwner())->GetOwningController();

		// Spawn parameters
		FVector Location = FVector(0.0f, 0.0f, 0.0f);
		FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = EquipmentOwner;

		//** Spawning equipment actors on the server **//

		// Vertical equipment
		HealthKit = GetWorld()->SpawnActor<ABaseEquipment>(VerticalEquipmentData.HealthKitData->Data.EquipmentSubclass, Location, Rotation, SpawnParameters);
		ExplosiveBomb = GetWorld()->SpawnActor<ABaseEquipment>(VerticalEquipmentData.ExplosiveBombData->Data.EquipmentSubclass, Location, Rotation, SpawnParameters);
		FireBomb = GetWorld()->SpawnActor<ABaseEquipment>(VerticalEquipmentData.FireBombData->Data.EquipmentSubclass, Location, Rotation, SpawnParameters);
		SupportBomb = GetWorld()->SpawnActor<ABaseEquipment>(VerticalEquipmentData.SupportBombData->Data.EquipmentSubclass, Location, Rotation, SpawnParameters);

		// Horizontal equipment
		ShortWeapon = GetWorld()->SpawnActor<ABaseEquipment>(HorizontalEquipmentData.ShortWeaponData->Data.EquipmentSubclass, Location, Rotation, SpawnParameters);
		LargeWeapon = GetWorld()->SpawnActor<ABaseEquipment>(HorizontalEquipmentData.LargeWeaponData->Data.EquipmentSubclass, Location, Rotation, SpawnParameters);

		OnRep_HealthKit();
		OnRep_ExplosiveBomb();
		OnRep_FireBomb();
		OnRep_SupportBomb();
		OnRep_ShortWeapon();
		OnRep_LargeWeapon();

		GetOwner()->ForceNetUpdate();
	}

}

void UInventoryComponent::ResetInventory()
{
	HealthKit->ResetEquipment();
	ExplosiveBomb->ResetEquipment();
	FireBomb->ResetEquipment();
	SupportBomb->ResetEquipment();
	ResetWeapons();
}

void UInventoryComponent::ResetWeapons()
{
	ShortWeapon->ResetEquipment();
	LargeWeapon->ResetEquipment();
}

void UInventoryComponent::SetOwningCharacter(ACharacter* Character)
{
	if (GetOwner()->HasAuthority())
	{
		HealthKit->SetInstigator(Character);
		FireBomb->SetInstigator(Character);
		ExplosiveBomb->SetInstigator(Character);
		SupportBomb->SetInstigator(Character);
		ShortWeapon->SetInstigator(Character);
		LargeWeapon->SetInstigator(Character);	
	}

	HealthKit->OwningCharacter = Character;
	FireBomb->OwningCharacter = Character;
	ExplosiveBomb->OwningCharacter = Character;
	SupportBomb->OwningCharacter = Character;
	ShortWeapon->OwningCharacter = Character;
	LargeWeapon->OwningCharacter = Character;
}

void UInventoryComponent::SetSelection(const int32 NewValue)
{
	// Requests the server to change the value if new value is different from current value
	if (!GetOwner()->HasAuthority())
	{
		if (NewValue != Selection)
		{
			Server_SetSelection(NewValue);
		}
	}

	// Updates immediatelly on the caller
	Selection = NewValue;
	OnRep_Selection();

	// Forces net update if caller is server
	GetOwner()->ForceNetUpdate();
}

void UInventoryComponent::OffsetVerticalSelection(const int32 Offset)
{
	const int32 NewSelection = FMath::Clamp<int32>(Selection + Offset, 5, 8);
	SetSelection(NewSelection);
}

void UInventoryComponent::OffsetHorizontalSelection(const int32 Offset)
{
	const int32 NewSelection = FMath::Clamp<int32>(Selection + Offset, 1, 2);
	SetSelection(NewSelection);
}

int32 UInventoryComponent::GetSelection() const
{
	return Selection;
}

ABaseEquipment* UInventoryComponent::GetSelectionEquipment(const int32 Value)
{

	switch (Value)
	{
	case SLOT_EXPLOSIVE_BOMB:
		return ExplosiveBomb;

	case SLOT_HEALTH_KIT:
		return HealthKit;

	case SLOT_FIRE_BOMB:
		return FireBomb;

	case SLOT_SUPPORT_BOMB:
		return SupportBomb;

	case SLOT_SHORT_WEAPON:
		return ShortWeapon;

	case SLOT_LARGE_WEAPON:
		return LargeWeapon;

	default:
		return nullptr;
	}
}

ABaseEquipment* UInventoryComponent::GetCurrentEquipment()
{
	return GetSelectionEquipment(Selection);
}

bool UInventoryComponent::IsWeaponEquipped() const
{
	return (Selection >= 1 && Selection <= 4);
}

void UInventoryComponent::OnRep_Selection()
{
	// Does not call unequip/equip on equipment if selection did not change
	if (PreviousSelection != Selection)
	{
		if (auto CurrentEquipment = GetSelectionEquipment(Selection))
		{
			if (CurrentEquipment->CanBeEquipped())
			{
				if (auto PreviousEquipment = GetSelectionEquipment(PreviousSelection))
				{
					PreviousEquipment->Unequip();
				}
				CurrentEquipment->Equip();
				OnEquippedUpdated.Broadcast(CurrentEquipment);
			}
		}
		PreviousSelection = Selection;
	}

	// Calls updated event even if selection did not change
	// Makes sure UI hotbar is still displayed
	OnSelectionUpdated.Broadcast(Selection);
}

void UInventoryComponent::OnRep_HealthKit()
{
	OnHealthKitUpdated.Broadcast(HealthKit);
}

void UInventoryComponent::OnRep_ExplosiveBomb()
{
	OnExplosiveUpdated.Broadcast(ExplosiveBomb);
}

void UInventoryComponent::OnRep_FireBomb()
{
	OnFireBombUpdated.Broadcast(FireBomb);
}

void UInventoryComponent::OnRep_SupportBomb()
{
	OnSupportBombUpdated.Broadcast(SupportBomb);
}

void UInventoryComponent::OnRep_ShortWeapon()
{
	OnShortWeaponUpdated.Broadcast(ShortWeapon);
}

void UInventoryComponent::OnRep_LargeWeapon()
{
	OnLargeWeaponUpdated.Broadcast(LargeWeapon);
}

void UInventoryComponent::Server_SetSelection_Implementation(const int32 NewValue)
{
	Selection = NewValue;
	OnRep_Selection();

	GetOwner()->ForceNetUpdate();
}

bool UInventoryComponent::Server_SetSelection_Validate(const int32 NewValue)
{
	// TODO: Implement RPC validation
	return true;
}

