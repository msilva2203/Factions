// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "Factions/Data/GameModeData.h"

#include "DataSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API UDataSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintCallable, Category = "Factions Data")
	void PushGameModeData(TArray<UGameModeData*> NewData);

	UFUNCTION(BlueprintCallable, Category = "Factions Data")
	UGameModeData* GetGameModeData(const EFactionsGameMode GameMode);

	UPROPERTY(BlueprintReadOnly, Category = "Factions Data")
	TArray<UGameModeData*> FactionsGameModeData;
};
