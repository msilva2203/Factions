// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameStateBase.h"
#include "Factions/Subsystems/FactionsSessionSubsystem.h"

#include "MasterGameState.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AMasterGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AMasterGameState();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Master Game State")
	UFactionsSessionSubsystem* FactionsSessionSubsystem;
};
