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
	Crouching		UMETA(DisplayName = "CROUCHING")
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

};

UCLASS()
class FACTIONS_API AMasterCharacter : public ACharacter, public IFactionsEntityInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMasterCharacter();

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(EditAnywhere, Category = "Character")
	USpringArmComponent* CameraArm;

	UPROPERTY(EditAnywhere, Category = "Character")
	UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, Category = "Character")
	URadarEntityComponent* RadarEntityComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	URadarSubsystem* RadarSubsystem;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	UFactionsSessionSubsystem* FactionsSessionSubsystem;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual EFactionsTeam GetEntityTeam() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnCharacterStateUpdated(const ECharacterState UpdatedCharacterState, const bool bState);

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnMovementStateUpdated(const EMovementState UpdatedMovementState, const bool bState);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetCharacterState(const ECharacterState NewCharacterState);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void SetMovementState(const EMovementState NewMovementState);

	UFUNCTION()
	void OnRep_CharacterState();

	UFUNCTION()
	void OnRep_MovementState();

	UPROPERTY(ReplicatedUsing = "OnRep_CharacterState", BlueprintReadOnly, Category = "Character")
	ECharacterState CharacterState;

	UPROPERTY(ReplicatedUsing = "OnRep_MovementState", BlueprintReadOnly, Category = "Character")
	EMovementState MovementState;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	FInputData InputData;

private:
	UFUNCTION(Server, Reliable)
	void Server_SetCharacterState(const ECharacterState NewCharacterState);
	void Server_SetCharacterState_Implementation(const ECharacterState NewCharacterState);
	bool Server_SetCharacterState_Validate(const ECharacterState NewCharacterState);

	UFUNCTION(Server, Reliable)
	void Server_SetMovementState(const EMovementState NewMovementState);
	void Server_SetMovementState_Implementation(const EMovementState NewMovementState);
	bool Server_SetMovementState_Validate(const EMovementState NewMovementState);

	UFUNCTION()
	void UpdateCharacterState(const ECharacterState UpdatedCharacterState, const bool bState);

	UFUNCTION()
	void UpdateMovementState(const EMovementState UpdatedMovementState, const bool bState);

	UPROPERTY()
	ECharacterState PreviousCharacterState;

	UPROPERTY()
	EMovementState PreviousMovementState;

};
