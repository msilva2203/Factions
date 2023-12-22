// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Factions/Components/RadarEntityComponent.h"
#include "Factions/Subsystems/RadarSubsystem.h"
#include "Factions/Interfaces/FactionsEntityInterface.h"

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

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	URadarSubsystem* RadarSubsystem;

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

private:
	UFUNCTION(Server, Reliable)
	void Server_SetCharacterState(const ECharacterState NewCharacterState);

	UFUNCTION(Server, Reliable)
	void Server_SetMovementState(const EMovementState NewMovementState);

	UFUNCTION()
	void Server_SetCharacterState_Implementation(const ECharacterState NewCharacterState);

	UFUNCTION()
	void Server_SetMovementState_Implementation(const EMovementState NewMovementState);

	UFUNCTION()
	void UpdateCharacterState(const ECharacterState UpdatedCharacterState, const bool bState);

	UFUNCTION()
	void UpdateMovementState(const EMovementState UpdatedMovementState, const bool bState);

	UPROPERTY()
	ECharacterState PreviousCharacterState;

	UPROPERTY()
	EMovementState PreviousMovementState;

};
