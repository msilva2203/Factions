// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectionUpdatedDelegate, const int32, NewValue);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTIONS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void SetSelection(const int32 NewValue);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void OffsetVerticalSelection(const int32 Offset);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void OffsetHorizontalSelection(const int32 Offset);

	UFUNCTION(BlueprintPure, Category = "Inventory")
	int32 GetSelection() const;

	UPROPERTY(ReplicatedUsing = "OnRep_Selection", BlueprintReadOnly, Category = "Inventory")
	int32 Selection;

	UPROPERTY(BlueprintAssignable, Category = "Inventory");
	FOnSelectionUpdatedDelegate OnSelectionUpdated;

protected:
	UFUNCTION()
	virtual void OnRep_Selection();

	UFUNCTION(Server, Unreliable)
	void Server_SetSelection(const int32 NewValue);
	void Server_SetSelection_Implementation(const int32 NewValue);
	bool Server_SetSelection_Validate(const int32 NewValue);
};
