// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageDealersStack.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FACTIONS_API UDamageDealersStack : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDamageDealersStack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Damage Dealers Stack")
	void ClearStack();

	UFUNCTION(BlueprintCallable, Category = "Damage Dealers Stack")
	void PushActor(AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Damage Dealers Stack")
	AActor* GetMainActor() const;

	UFUNCTION(BlueprintPure, Category = "Damage Dealers Stack")
	AActor* GetAssistActor() const;

private:
	UPROPERTY()
	AActor* MainActor;

	UPROPERTY()
	AActor* AssistActor;
};
