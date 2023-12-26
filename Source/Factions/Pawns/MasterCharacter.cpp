// Developed by the Factions community


#include "Factions/Pawns/MasterCharacter.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"

// Sets default values
AMasterCharacter::AMasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	// Components

	// Spring Arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm Component"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->TargetArmLength = 180.0f;

	// Camera
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera Component"));
	PlayerCamera->SetupAttachment(CameraArm);

	// Radar entity component
	RadarEntityComponent = CreateDefaultSubobject<URadarEntityComponent>(TEXT("Radar Entity Component"));
}

void AMasterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(AMasterCharacter, CharacterState);
	DOREPLIFETIME(AMasterCharacter, MovementState);
}

// Called when the game starts or when spawned
void AMasterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// General begin play

	// Caches a reference to the factions session subsytem
	FactionsSessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();

	if (IsLocallyControlled())
	{
		// Local player begin play

		// Caches a reference to the radar subsytem
		auto LocalPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();
		RadarSubsystem = LocalPlayer->GetSubsystem<URadarSubsystem>();

		RadarSubsystem->SetPhysicalRadius(1500.0f);
	}
	else
	{
		// Not local begin play

		RadarEntityComponent->PushEntity();
	}
}

void AMasterCharacter::InputMoveForward(float AxisValue)
{
	InputData.MoveForwardValue = AxisValue;
}

void AMasterCharacter::InputMoveRight(float AxisValue)
{
	InputData.MoveRightValue = AxisValue;
}

void AMasterCharacter::InputLookUp(float AxisValue)
{
	InputData.LookUpValue = AxisValue;
}

void AMasterCharacter::InputLookRight(float AxisValue)
{
	InputData.LookRightValue = AxisValue;
}

void AMasterCharacter::InputSprintPressed()
{
	InputData.bHoldingSprint = true;
}

void AMasterCharacter::InputSprintReleased()
{
	InputData.bHoldingSprint = false;
}

void AMasterCharacter::InputCrouchPressed()
{
	InputData.bHoldingCrouch = true;
}

void AMasterCharacter::InputCrouchReleased()
{
	InputData.bHoldingCrouch = false;
}

void AMasterCharacter::InputAimPressed()
{
	InputData.bHoldingAim = true;
}

void AMasterCharacter::InputAimReleased()
{
	InputData.bHoldingAim = false;
}

void AMasterCharacter::InputFirePressed()
{
	InputData.bHoldingFire = true;
}

void AMasterCharacter::InputFireReleased()
{
	InputData.bHoldingFire = false;
}

// Called every frame
void AMasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// General tick


	if (IsLocallyControlled())
	{
		// Local player tick

		// Updates radar center transform
		FRadarTransform CenterTransform;
		CenterTransform.Translation.X = GetActorLocation().X;
		CenterTransform.Translation.Y = GetActorLocation().Y;
		CenterTransform.Angle = GetControlRotation().Yaw + 90.0f;
		if (RadarSubsystem)
		{
			RadarSubsystem->UpdateCenterTransform(CenterTransform);
		}
	}
	else
	{
		// Not local tick

		// Updates radar entity icon transform 
		FRadarTransform RadarIconTransform;
		RadarIconTransform.Translation.X = GetActorLocation().X;
		RadarIconTransform.Translation.Y = GetActorLocation().Y;
		RadarEntityComponent->UpdateIconTransform(RadarIconTransform);

	}
}

// Called to bind functionality to input
void AMasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axis input events
	PlayerInputComponent->BindAxis("MoveForward", this, &AMasterCharacter::InputMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMasterCharacter::InputMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMasterCharacter::InputLookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AMasterCharacter::InputLookRight);

	// Bind action input events
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMasterCharacter::InputSprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMasterCharacter::InputSprintReleased);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMasterCharacter::InputCrouchPressed);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMasterCharacter::InputCrouchReleased);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMasterCharacter::InputAimPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AMasterCharacter::InputAimReleased);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMasterCharacter::InputFirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMasterCharacter::InputFireReleased);
}

EFactionsTeam AMasterCharacter::GetEntityTeam()
{
	IFactionsEntityInterface* Interface = Cast<IFactionsEntityInterface>(GetPlayerState());
	if (Interface)
	{
		return Interface->GetEntityTeam();
	}
	return EFactionsTeam::None;
}

void AMasterCharacter::SetCharacterState(const ECharacterState NewCharacterState)
{
	// Update character
	CharacterState = NewCharacterState;
	OnRep_CharacterState();
	Server_SetCharacterState(NewCharacterState);
}

void AMasterCharacter::SetMovementState(const EMovementState NewMovementState)
{
	// Update character
	MovementState = NewMovementState;
	OnRep_MovementState();
	Server_SetMovementState(NewMovementState);
}

void AMasterCharacter::OnRep_CharacterState()
{
	if (PreviousCharacterState != CharacterState)
	{
		UpdateCharacterState(PreviousCharacterState, false);
		UpdateCharacterState(CharacterState, true);

		PreviousCharacterState = CharacterState;
	}
}

void AMasterCharacter::OnRep_MovementState()
{
	if (PreviousMovementState != MovementState)
	{
		UpdateMovementState(PreviousMovementState, false);
		UpdateMovementState(MovementState, true);

		PreviousMovementState = MovementState;
	}
}

void AMasterCharacter::Server_SetCharacterState_Implementation(const ECharacterState NewCharacterState)
{
	CharacterState = NewCharacterState;
}

bool AMasterCharacter::Server_SetCharacterState_Validate(const ECharacterState NewCharacterState)
{
	// TODO: Implement RPC validation
	return true;
}

void AMasterCharacter::Server_SetMovementState_Implementation(const EMovementState NewMovementState)
{
	MovementState = NewMovementState;
}

bool AMasterCharacter::Server_SetMovementState_Validate(const EMovementState NewMovementState)
{
	// TODO: Implement RPC validation
	return true;
}

void AMasterCharacter::UpdateCharacterState(const ECharacterState UpdatedCharacterState, const bool bState)
{
	switch (UpdatedCharacterState)
	{
	case ECharacterState::Default:
		break;
	case ECharacterState::Aiming:
		break;
	case ECharacterState::Down:
		break;
	case ECharacterState::Backpack:
		break;
	default:
		break;
	}

	// Notify blueprint classes
	OnCharacterStateUpdated(UpdatedCharacterState, bState);
}

void AMasterCharacter::UpdateMovementState(const EMovementState UpdatedMovementState, const bool bState)
{
	switch (UpdatedMovementState)
	{
	case EMovementState::Standing:
		break;
	case EMovementState::Crouching:
		break;
	default:
		break;
	}

	// Notify blueprint classes
	OnMovementStateUpdated(UpdatedMovementState, bState);
}

