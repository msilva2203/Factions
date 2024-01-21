// Developed by the Factions community


#include "Factions/BaseActors/BaseEquipment.h"
#include "Factions/Data/EquipmentData.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ABaseEquipment::ABaseEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bAlwaysRelevant = true;
	bReplicates = true;
}

void ABaseEquipment::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABaseEquipment, Amount);
}

// Called when the game starts or when spawned
void ABaseEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ABaseEquipment::IsLocalInstance()
{
	auto LocalPlayer = GetWorld()->GetFirstPlayerController();
	return LocalPlayer == GetNetOwner();
}

void ABaseEquipment::Equip()
{
	if (GetOwner() == GetWorld()->GetFirstPlayerController())
	{
		EnableInput(GetWorld()->GetFirstPlayerController());
	}

	OnEquipped();
}

void ABaseEquipment::Unequip()
{
	DisableInput(GetWorld()->GetFirstPlayerController());
	SetPrimaryAction(false);

	OnUnequipped();
}

void ABaseEquipment::SetPrimaryAction(const bool bNewValue)
{
}

void ABaseEquipment::SetSecondaryAction(const bool bNewValue)
{
}

bool ABaseEquipment::IsWeapon() const
{
	return false;
}

void ABaseEquipment::SetAmount(const int32 NewValue)
{
	Amount = NewValue;
	OnRep_Amount();
}

void ABaseEquipment::OnRep_Amount()
{
	OnAmountUpdated.Broadcast(Amount);
}
