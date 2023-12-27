// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "EntityAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAtrributeUpdatedDelegate, const float, NewValue, const float, Percent);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTIONS_API UEntityAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEntityAttributeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Attribute Component")
	void SetAttributeValue(const float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Attribute Component")
	void OffsetAttributeValue(const float Offset);

	UFUNCTION(BlueprintPure, Category = "Attribute Component")
	float GetAttributeValue() const;

	UFUNCTION(BlueprintPure, Category = "Attribute Component")
	float GetPercent() const;

	UPROPERTY(BlueprintAssignable, Category = "Attribute Component")
	FOnAtrributeUpdatedDelegate OnAttributeUpdated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Component")
	FName AttributeName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Component")
	float DefaultAttributeValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Component")
	float MinValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attribute Component")
	float MaxValue;

protected:
	UPROPERTY(ReplicatedUsing = "OnRep_AttributeValue")
	float AttributeValue;

	UFUNCTION()
	void OnRep_AttributeValue();
};
