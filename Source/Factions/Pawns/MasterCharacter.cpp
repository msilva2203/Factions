// Developed by the Factions community


#include "Factions/Pawns/MasterCharacter.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"


#define MIN_SPRINTING_SPEED 50.0f


// Sets default values
AMasterCharacter::AMasterCharacter() :
	CharacterState(ECharacterState::Default),
	MovementState(EMovementState::Standing)
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

	// Health component
	HealthComponent = CreateDefaultSubobject<UEntityAttributeComponent>(TEXT("Health Attribute"));
	HealthComponent->SetIsReplicated(true);

	// Stamina component
	StaminaComponent = CreateDefaultSubobject<UEntityAttributeComponent>(TEXT("Stamina Attribute"));
	StaminaComponent->SetIsReplicated(false);

	// Listening stamina component
	ListeningStaminaComponent = CreateDefaultSubobject<UEntityAttributeComponent>(TEXT("Listening Stamina Attribute"));
	ListeningStaminaComponent->SetIsReplicated(false);

}

void AMasterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(AMasterCharacter, CharacterState);
	DOREPLIFETIME(AMasterCharacter, MovementState);
	DOREPLIFETIME(AMasterCharacter, Shoulder);
}

// Called when the game starts or when spawned
void AMasterCharacter::BeginPlay()
{
	Super::BeginPlay();

	// General begin play

	// Caches a reference to the factions session subsytem
	FactionsSessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();

	// Binds events to attribute values changes
	HealthComponent->OnAttributeUpdated.AddDynamic(this, &AMasterCharacter::HealthUpdated);
	StaminaComponent->OnAttributeUpdated.AddDynamic(this, &AMasterCharacter::StaminaUpdated);
	ListeningStaminaComponent->OnAttributeUpdated.AddDynamic(this, &AMasterCharacter::ListeningStaminaUpdated);

	// Update default character and movement states
	UpdateCharacterState(CharacterState, true);
	UpdateMovementState(MovementState, true);


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

	// Authority begin play
	if (HasAuthority())
	{
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

	// Crouch toggle
	if (IsCrouching())
	{
		SetMovementState(EMovementState::Standing);
	}
	else
	{
		SetMovementState(EMovementState::Crouching);
	}
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

	// Handles both character and movement states
	HandleCharacterState(DeltaTime, IsLocallyControlled());
	HandleMovementState(DeltaTime, IsLocallyControlled());

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
	Server_SetCharacterState(NewCharacterState);

	if (!HasAuthority())
	{
		CharacterState = NewCharacterState;
		OnRep_CharacterState();
	}
}

void AMasterCharacter::SetMovementState(const EMovementState NewMovementState)
{
	// Update character
	Server_SetMovementState(NewMovementState);

	if (!HasAuthority())
	{
		MovementState = NewMovementState;
		OnRep_MovementState();
	}
}

void AMasterCharacter::SetShoulder(const EShoulder NewShoulder)
{
	// Update character
	Server_SetShoulder(NewShoulder);

	if (!HasAuthority())
	{
		Shoulder = NewShoulder;
		OnRep_Shoulder();
	}
}

bool AMasterCharacter::IsInDefaultState() const
{
	return CharacterState == ECharacterState::Default;
}

bool AMasterCharacter::IsAiming() const
{
	return CharacterState == ECharacterState::Aiming;
}

bool AMasterCharacter::IsDown() const
{
	return CharacterState == ECharacterState::Down;
}

bool AMasterCharacter::IsInBackpack() const
{
	return CharacterState == ECharacterState::Backpack;
}

bool AMasterCharacter::IsStanding() const
{
	return MovementState == EMovementState::Standing;
}

bool AMasterCharacter::IsCrouching() const
{
	return MovementState == EMovementState::Crouching;
}

bool AMasterCharacter::IsSprinting() const
{
	return MovementState == EMovementState::Sprinting;
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

void AMasterCharacter::OnRep_Shoulder()
{
	UpdateShoulder(Shoulder);
}

void AMasterCharacter::Server_SetCharacterState_Implementation(const ECharacterState NewCharacterState)
{
	CharacterState = NewCharacterState;
	OnRep_CharacterState();
}

bool AMasterCharacter::Server_SetCharacterState_Validate(const ECharacterState NewCharacterState)
{
	// TODO: Implement RPC validation
	return true;
}

void AMasterCharacter::Server_SetMovementState_Implementation(const EMovementState NewMovementState)
{
	MovementState = NewMovementState;
	OnRep_MovementState();
}

bool AMasterCharacter::Server_SetMovementState_Validate(const EMovementState NewMovementState)
{
	// TODO: Implement RPC validation
	return true;
}

void AMasterCharacter::Server_SetShoulder_Implementation(const EShoulder NewShoulder)
{
	Shoulder = NewShoulder;
	OnRep_Shoulder();
}

bool AMasterCharacter::Server_SetShoulder_Validate(const EShoulder NewShoulder)
{
	// TODO: Implement RPC validation
	return true;
}

void AMasterCharacter::UpdateCharacterState(const ECharacterState UpdatedCharacterState, const bool bState)
{
	switch (UpdatedCharacterState)
	{
	case ECharacterState::Default:

		// Default State update

		if (bState)
		{
			if (!IsSprinting() && InputData.bHoldingSprint)
			{
				SetMovementState(EMovementState::Sprinting);
			}
		}
		else
		{

		}

		//...
		break;
	case ECharacterState::Aiming:

		// Aiming State updated

		if (bState)
		{
			if (IsSprinting())
			{
				SetMovementState(EMovementState::Standing);
			}
		}
		else
		{

		}

		//...
		break;
	case ECharacterState::Down:

		// Down State updated

		if (bState)
		{

		}
		else
		{

		}

		//...
		break;
	case ECharacterState::Backpack:

		// Backpack State updated

		if (bState)
		{

		}
		else
		{

		}

		//...
		break;
	default:
		break;
	}

	// Notify blueprint classes
	OnCharacterStateUpdated(UpdatedCharacterState, bState);
}

void AMasterCharacter::HandleCharacterState(float DeltaTime, const bool bIsLocal)
{

}

void AMasterCharacter::UpdateMovementState(const EMovementState UpdatedMovementState, const bool bState)
{
	auto CharMovement = GetCharacterMovement();

	switch (UpdatedMovementState)
	{
	case EMovementState::Standing:

		// Standing State updated

		if (bState)
		{
			MovementData = StandingMovementData->Data;
			CharMovement->MaxWalkSpeed = MovementData.Speed;
		}
		else
		{

		}

		//...
		break;
	case EMovementState::Crouching:

		// Crouching State updated

		if (bState)
		{
			MovementData = CrouchingMovementData->Data;
			CharMovement->MaxWalkSpeed = MovementData.Speed;
		}
		else
		{

		}

		//...
		break;
	case EMovementState::Sprinting:

		// Sprinting State updated

		if (bState)
		{
			MovementData = SprintingMovementData->Data;
			CharMovement->MaxWalkSpeed = MovementData.Speed;
		}
		else
		{

		}

		//...
		break;
	default:
		break;
	}

	// Notify blueprint classes
	OnMovementStateUpdated(UpdatedMovementState, bState);
}

void AMasterCharacter::HandleMovementState(float DeltaTime, const bool bIsLocal)
{
	const float MovingSpeed = GetVelocity().Length();

	if (IsSprinting())
	{
		StaminaComponent->OffsetAttributeValue(-10.0f * DeltaTime);
	}
	else
	{
		StaminaComponent->OffsetAttributeValue(13.5f * DeltaTime);
	}

	if (IsSprinting() && MovingSpeed <= MIN_SPRINTING_SPEED)
	{
		SetMovementState(EMovementState::Standing);
	}

	if (bIsLocal)
	{
		// Sprinting input
		if (InputData.bHoldingSprint)
		{
			if (!IsSprinting() && MovingSpeed > MIN_SPRINTING_SPEED && StaminaComponent->GetPercent() >= 0.25f)
			{
				SetMovementState(EMovementState::Sprinting);
			}
		}
		else
		{
			if (IsSprinting())
			{
				SetMovementState(EMovementState::Standing);
			}
		}
		
		// Crouch input

	}
	else
	{
		//...
	}

	
}

void AMasterCharacter::UpdateShoulder(const EShoulder NewShoulder)
{
	// Notify blueprint classes
	OnShoulderUpdated(NewShoulder);
}

void AMasterCharacter::HealthUpdated(const float NewValue, const float Percent)
{

}

void AMasterCharacter::StaminaUpdated(const float NewValue, const float Percent)
{
	if (NewValue <= 0.0f)
	{
		if (IsSprinting())
		{
			SetMovementState(EMovementState::Standing);
		}
	}
}

void AMasterCharacter::ListeningStaminaUpdated(const float NewValue, const float Percent)
{

}
