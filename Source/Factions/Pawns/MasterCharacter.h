// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Factions/Components/RadarEntityComponent.h"
#include "Factions/Subsystems/RadarSubsystem.h"
#include "Factions/Interfaces/FactionsEntityInterface.h"
#include "Factions/Subsystems/FactionsSessionSubsystem.h"
#include "Factions/Data/MovementData.h"
#include "Factions/Components/EntityAttributeComponent.h"
#include "Factions/Data/CameraData.h"
#include "Factions/Subsystems/SettingsSubsystem.h"
#include "Factions/Components/InventoryComponent.h"
#include "Components/WidgetComponent.h"
#include "Factions/Widgets/DownDisplay.h"
#include "Factions/Widgets/NameTag.h"
#include "Components/ViewportWidgetComponent.h"
#include "Factions/Components/DamageDealersStack.h"

#include "MasterCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	Default			UMETA(DisplayName = "DEFAULT"),
	Aiming			UMETA(DisplayName = "AIMING"),
	Down			UMETA(DisplayName = "DOWN"),
	Backpack		UMETA(DisplayName = "BACKPACK")
};

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Standing		UMETA(DisplayName = "STANDING"),
	Crouching		UMETA(DisplayName = "CROUCHING"),
	Sprinting		UMETA(DisplayName = "SPRINTING"),
	Idle			UMETA(DisplayName = "IDLE")
};

UENUM(BlueprintType)
enum class EShoulder : uint8
{
	Left			UMETA(DisplayName = "LEFT"),
	Center			UMETA(DisplayName = "CENTER"),
	Right			UMETA(DisplayName = "RIGHT")
};

USTRUCT(BlueprintType)
struct FInputData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float MoveForwardValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float MoveRightValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookUpValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	float LookRightValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bHoldingSprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bHoldingCrouch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bHoldingAim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bHoldingFire;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bHoldingSwitchShoulder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bBlockShoulderSwitch;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	bool bIsHotBarVisible;

};

// Delegate declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCharacterStateUpdatedDelegate, ECharacterState, NewValue, bool, bNewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMovementStateUpdatedDelegate, EMovementState, NewValue, bool, bNewState);

UCLASS()
class FACTIONS_API AMasterCharacter : public ACharacter, public IFactionsEntityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	//
	// Components
	//

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	URadarEntityComponent* RadarEntityComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UEntityAttributeComponent* HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UEntityAttributeComponent* DownHealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UEntityAttributeComponent* StaminaComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UEntityAttributeComponent* ListeningStaminaComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UDamageDealersStack* DamageDealersStack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	UViewportWidgetComponent* NameTagViewportWidgetComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	UInventoryComponent* InventoryComponent;

	//
	// Movement Data
	//

	UPROPERTY(EditAnywhere, Category = "Character Movement")
	UMovementData* StandingMovementData;

	UPROPERTY(EditAnywhere, Category = "Character Movement")
	UMovementData* CrouchingMovementData;

	UPROPERTY(EditAnywhere, Category = "Character Movement")
	UMovementData* SprintingMovementData;

	//
	// Camera Data
	//

	UPROPERTY(EditAnywhere, Category = "Character Camera")
	UCameraData* StandingCameraData;

	UPROPERTY(EditAnywhere, Category = "Character Camera")
	UCameraData* CrouchingCameraData;

	UPROPERTY(EditAnywhere, Category = "Character Camera")
	UCameraData* SprintingCameraData;

	UPROPERTY(EditAnywhere, Category = "Character Camera")
	UCameraData* AimingCameraData;

	UPROPERTY(EditAnywhere, Category = "Character Camera")
	UCameraData* BackpackCameraData;

	UPROPERTY(EditDefaultsOnly, Category = "Character Camera")
	float FreeCameraInterpSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Character Camera")
	float BlockedCameraInterpSpeed;

	//
	// UI Data
	//

	UPROPERTY(EditDefaultsOnly, Category = "Character Radar")
	TSubclassOf<UBaseRadarIcon> RadarTeammateIconClass;

	UPROPERTY(EditDefaultsOnly, Category = "Character Radar")
	TSubclassOf<UBaseRadarIcon> RadarEnemyIconClass;

	UPROPERTY(EditDefaultsOnly, Category = "Character Name Tag")
	TSubclassOf<UNameTag> TeammateNameTagClass;

	UPROPERTY(EditDefaultsOnly, Category = "Character Name Tag")
	TSubclassOf<UNameTag> EnemyNameTagClass;

	//
	// Widgets
	//

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	UNameTag* NameTagWidget;

	//
	// Delegates
	//

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCharacterStateUpdatedDelegate OnCharacterStateUpdatedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnMovementStateUpdatedDelegate OnMovementStateUpdatedDelegate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnSetupPlayerCharacter();

	UFUNCTION()
	virtual void SetupPlayerCharacter();

	UFUNCTION()
	virtual void OnInventorySelectionUpdated(const int32 NewValue);

	virtual void OnRep_PlayerState() override;

	UFUNCTION()
	virtual void InputMoveForward(float AxisValue);

	UFUNCTION()
	virtual void InputMoveRight(float AxisValue);

	UFUNCTION()
	virtual void InputLookUp(float AxisValue);

	UFUNCTION()
	virtual void InputLookRight(float AxisValue);

	UFUNCTION()
	virtual void InputSprintPressed();

	UFUNCTION()
	virtual void InputSprintReleased();

	UFUNCTION()
	virtual void InputCrouchPressed();

	UFUNCTION()
	virtual void InputCrouchReleased();

	UFUNCTION()
	virtual void InputAimPressed();

	UFUNCTION()
	virtual void InputAimReleased();

	UFUNCTION()
	virtual void InputFirePressed();

	UFUNCTION()
	virtual void InputFireReleased();

	UFUNCTION()
	virtual void InputSwitchShoulderPressed();

	UFUNCTION()
	virtual void InputSwitchShoulderReleased();

	UFUNCTION()
	virtual void InputSelectRightPressed();

	UFUNCTION()
	virtual void InputSelectLeftPressed();

	UFUNCTION()
	virtual void InputSelectUpPressed();

	UFUNCTION()
	virtual void InputSelectDownPressed();

	UFUNCTION()
	virtual void InputSwitchBackpackPressed();

	UFUNCTION()
	virtual void InputSwitchBackpackReleased();

	UFUNCTION()
	void InputCompleteShoulderSwitchDelay();

	UFUNCTION()
	void InputDisplayHotBar();

	UFUNCTION()
	void InputHideHotBar();

	UFUNCTION(BlueprintPure, Category = "Character")
	float GetSensitivityX() const;

	UFUNCTION(BlueprintPure, Category = "Character")
	float GetSensitivityY() const;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	URadarSubsystem* RadarSubsystem;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	UFactionsSessionSubsystem* FactionsSessionSubsystem;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	USettingsSubsystem* SettingsSubsystem;

	//
	// Timers
	//

	UPROPERTY()
	FTimerHandle ShoulderSwitchDelayHandle;

	UPROPERTY()
	FTimerHandle HotBarVisibilityTimeHandle;

	UPROPERTY()
	FTimerHandle DownTimeHandle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual EFactionsTeam GetEntityTeam() override;
	virtual void DamageEntity(float Damage, AActor* DamageInstigator, AActor* Causer) override;
	virtual bool IsTeammate() override;

	UFUNCTION()
	void Kill();

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnCharacterStateUpdated(const ECharacterState UpdatedCharacterState, const bool bState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnMovementStateUpdated(const EMovementState UpdatedMovementState, const bool bState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnShoulderUpdated(const EShoulder NewShoulder);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetCharacterState(const ECharacterState NewCharacterState);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetMovementState(const EMovementState NewMovementState);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetShoulder(const EShoulder NewShoulder);

	UFUNCTION(BlueprintPure, Category = "Character")
	float GetDownTime();

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsInDefaultState() const;

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsAiming() const;

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsDown() const;

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsInBackpack() const;

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsStanding() const;

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsCrouching() const;

	UFUNCTION(BlueprintPure, Category = "Character")
	bool IsSprinting() const;

	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_MovementState();

	UFUNCTION()
	void OnRep_Shoulder();

	UPROPERTY(ReplicatedUsing = "OnRep_CharacterState", BlueprintReadOnly, Category = "Character")
	ECharacterState CharacterState;

	UPROPERTY(ReplicatedUsing = "OnRep_MovementState", BlueprintReadOnly, Category = "Character")
	EMovementState MovementState;

	UPROPERTY(ReplicatedUsing = "OnRep_Shoulder", BlueprintReadOnly, Category = "Character")
	EShoulder Shoulder;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FInputData InputData;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FFactionsMovementData MovementData;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FFactionsCameraData CameraData;

private:
	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetCharacterState(const ECharacterState NewCharacterState);
	void Server_SetCharacterState_Implementation(const ECharacterState NewCharacterState);
	bool Server_SetCharacterState_Validate(const ECharacterState NewCharacterState);

	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetMovementState(const EMovementState NewMovementState);
	void Server_SetMovementState_Implementation(const EMovementState NewMovementState);
	bool Server_SetMovementState_Validate(const EMovementState NewMovementState);

	UFUNCTION(Server, Unreliable, WithValidation)
	void Server_SetShoulder(const EShoulder NewShoulder);
	void Server_SetShoulder_Implementation(const EShoulder NewShoulder);
	bool Server_SetShoulder_Validate(const EShoulder NewShoulder);

	UFUNCTION()
	void UpdateCharacterState(const ECharacterState UpdatedCharacterState, const bool bState);

	UFUNCTION()
	void HandleCharacterState(float DeltaTime, const bool bIsLocal);

	UFUNCTION()
	void UpdateMovementState(const EMovementState UpdatedMovementState, const bool bState);

	UFUNCTION()
	void HandleMovementState(float DeltaTime, const bool bIsLocal);

	UFUNCTION()
	void UpdateShoulder(const EShoulder NewShoulder);

	UFUNCTION()
	void HandleCamera(float DeltaTime, const bool bIsLocal);

	UFUNCTION()
	void HealthUpdated(const float NewValue, const float Percent);

	UFUNCTION()
	void DownHealthUpdated(const float NewValue, const float Percent);

	UFUNCTION()
	void StaminaUpdated(const float NewValue, const float Percent);

	UFUNCTION()
	void ListeningStaminaUpdated(const float NewValue, const float Percent);

	UPROPERTY()
	ECharacterState PreviousCharacterState;

	UPROPERTY()
	EMovementState PreviousMovementState;

};
