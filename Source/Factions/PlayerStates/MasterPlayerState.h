// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"
#include "Factions/Interfaces/FactionsEntityInterface.h"
#include "Factions/Factions.h"

#include "MasterPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerArrivedDelegate);

/**
 * 
 */
UCLASS()
class FACTIONS_API AMasterPlayerState : public APlayerState, public IFactionsEntityInterface
{
	GENERATED_BODY()
	
	AMasterPlayerState();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void OnRep_PlayerName() override;

	virtual EFactionsTeam GetEntityTeam() override;

	/**
	* Player arrived event, used to update lobby player lists
	*/
	UPROPERTY(BlueprintAssignable, Category = "Master Player State")
	FOnPlayerArrivedDelegate OnPlayerArrived;

	UPROPERTY(BlueprintReadOnly, Category = "Master Player State")
	bool bArrived;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerTeam, BlueprintReadOnly, Category = "Master Player State")
	EFactionsTeam PlayerTeam;

protected:
	UFUNCTION()
	virtual void OnRep_PlayerTeam();
};
