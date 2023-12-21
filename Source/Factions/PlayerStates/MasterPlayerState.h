// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MasterPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerArrivedDelegate);

/**
 * 
 */
UCLASS()
class FACTIONS_API AMasterPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	AMasterPlayerState();

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnRep_PlayerName() override;

	/**
	* Player arrived event, used to update lobby player lists
	*/
	UPROPERTY(BlueprintAssignable, Category = "Master Player State")
	FOnPlayerArrivedDelegate OnPlayerArrived;

	UPROPERTY(BlueprintReadOnly, Category = "Master Player State")
	bool bArrived;
};
