// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerState.h"
#include "Factions/Interfaces/FactionsEntityInterface.h"
#include "Factions/Factions.h"

#include "MasterPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerArrivedDelegate, AMasterPlayerState*, Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamUpdatedDelegate, EFactionsTeam, Team);

/**
 * 
 */
UCLASS()
class FACTIONS_API AMasterPlayerState : public APlayerState, public IFactionsEntityInterface
{
	GENERATED_BODY()
	
public:
	AMasterPlayerState(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void CopyProperties(APlayerState* PlayerState) override;

	virtual void OnRep_PlayerName() override;

	virtual EFactionsTeam GetEntityTeam() override;

	UFUNCTION()
	void SetPlayerTeam(const EFactionsTeam NewTeam);

	/**
	* Player arrived event, used to update lobby player lists
	*/
	UPROPERTY(BlueprintAssignable, Category = "Master Player State")
	FOnPlayerArrivedDelegate OnPlayerArrived;

	UPROPERTY(BlueprintAssignable, Category = "Master Player State")
	FOnTeamUpdatedDelegate OnPlayerTeamUpdated;

	UPROPERTY(BlueprintReadOnly, Category = "Master Player State")
	bool bArrived;

	UPROPERTY(ReplicatedUsing = OnRep_PlayerTeam, BlueprintReadOnly, Category = "Master Player State")
	EFactionsTeam PlayerTeam;

protected:
	UFUNCTION()
	virtual void OnRep_PlayerTeam();
};
