// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/PlayerStates/MasterPlayerState.h"
#include "Factions/Components/InventoryComponent.h"

#include "MatchPlayerState.generated.h"

UENUM(BlueprintType)
enum class EPlayerMatchState : uint8
{
	None			UMETA(DisplayName = "NONE"),
	Loading			UMETA(DisplayName = "LOADING"),
	Spectating		UMETA(DisplayName = "SPECTATING"),
	Playing			UMETA(DisplayName = "PLAYING")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerMatchStateUpdatedDelegate, EPlayerMatchState, PlayerMatchState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeadUpdatedDelegate, const bool, bIsDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerPointsUpdatedDelegate, const int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnRewardNotificationDelegate, const ERewardAction, RewardAction, int32, Reward);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDownsUpdatedDelegate, const int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerExecutionsUpdatedDelegate, const int32, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDeathsUpdatedDelegate, const int32, NewValue);

/**
 * 
 */
UCLASS()
class FACTIONS_API AMatchPlayerState : public AMasterPlayerState
{
	GENERATED_BODY()
	
public:
	AMatchPlayerState(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual bool IsEntityDead() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UInventoryComponent* InventoryComponent;

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void SetPlayerMatchState(const EPlayerMatchState NewValue);

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void SetIsDead(const bool bNewValue);

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void AddReward(const ERewardAction RewardAction);

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void AddDown();

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void AddExecution();

	UFUNCTION(BlueprintCallable, Category = "Match Player State")
	void AddDeath();

	UPROPERTY(ReplicatedUsing = OnRep_PlayerMatchState, BlueprintReadOnly, Category = "Match Player State")
	EPlayerMatchState PlayerMatchState;

	UPROPERTY(ReplicatedUsing = OnRep_IsDead, BlueprintReadOnly, Category = "Match Player State")
	bool bIsDead;

	UPROPERTY(ReplicatedUsing = OnRep_Points, BlueprintReadOnly, Category = "Match Player State")
	int32 Points;

	UPROPERTY(ReplicatedUsing = OnRep_Downs, BlueprintReadOnly, Category = "Match Player State")
	int32 Downs;

	UPROPERTY(ReplicatedUsing = OnRep_Executions, BlueprintReadOnly, Category = "Match Player State")
	int32 Executions;

	UPROPERTY(ReplicatedUsing = OnRep_Deaths, BlueprintReadOnly, Category = "Match Player State")
	int32 Deaths;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnPlayerMatchStateUpdatedDelegate OnPlayerMatchStateUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnPlayerDeadUpdatedDelegate OnPlayerDeadUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnPlayerPointsUpdatedDelegate OnPlayerPointsUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnPlayerDownsUpdatedDelegate OnPlayerDownsUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnPlayerExecutionsUpdatedDelegate OnPlayerExecutionsUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnPlayerDeathsUpdatedDelegate OnPlayerDeathsUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Match Player State")
	FOnRewardNotificationDelegate OnRewardNotification;

protected:
	UFUNCTION()
	void OnRep_IsDead();

	UFUNCTION()
	void OnRep_Points();

	UFUNCTION()
	void OnRep_Downs();

	UFUNCTION()
	void OnRep_Executions();

	UFUNCTION()
	void OnRep_Deaths();

	UFUNCTION()
	void OnRep_PlayerMatchState();

private:
	UFUNCTION(Client, Unreliable)
	void Client_SendRewardNotification(const ERewardAction RewardAction);
	void Client_SendRewardNotification_Implementation(const ERewardAction RewardAction);
};
