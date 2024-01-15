// Developed by the Factions community


#include "Factions/Pawns/MasterCharacter.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Factions/PlayerStates/MatchPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"


#define MIN_SPRINTING_SPEED 50.0f
#define SHOULDER_SWITCH_DELAY 0.5f
#define MIN_SHOULDER_SWAP_SPED 25.0f
#define HOTBAR_VISIBILITY_TIME 2.0f
#define CAMERA_HEIGHT 70.0f

#define CAMERA_INTERP_SPEED_FREE 5.0f
#define CAMERA_INTERP_SPEED_BLOCKED 50.0f


// Sets default values
AMasterCharacter::AMasterCharacter() :
	FreeCameraInterpSpeed(CAMERA_INTERP_SPEED_FREE),
	BlockedCameraInterpSpeed(CAMERA_INTERP_SPEED_BLOCKED),
	CharacterState(ECharacterState::Default),
	MovementState(EMovementState::Standing),
	Shoulder(EShoulder::Right)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	// Components

	// Spring Arm
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Arm Component"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->SetRelativeLocation(FVector(0.0f, 0.0f, CAMERA_HEIGHT));
	CameraArm->bUsePawnControlRotation = true;
	CameraArm->TargetArmLength = 180.0f;
	CameraArm->SetAbsolute(false, false, false);

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

	//** Inventory component changed to player state **//
	
	//// Inventory component
	//InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	//InventoryComponent->SetIsReplicated(true);

	//**//

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

	//** General begin play **//
	auto LocalPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();

	// Caches a reference to the factions session subsytem
	FactionsSessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();

	// Binds events to attribute values changes
	HealthComponent->OnAttributeUpdated.AddDynamic(this, &AMasterCharacter::HealthUpdated);
	StaminaComponent->OnAttributeUpdated.AddDynamic(this, &AMasterCharacter::StaminaUpdated);
	ListeningStaminaComponent->OnAttributeUpdated.AddDynamic(this, &AMasterCharacter::ListeningStaminaUpdated);

	// Update default character and movement states
	//UpdateCharacterState(CharacterState, true);
	//UpdateMovementState(MovementState, true);

	// Updates shoulder
	UpdateShoulder(Shoulder);

	// Caches a reference to the setting subsystem
	SettingsSubsystem = LocalPlayer->GetSubsystem<USettingsSubsystem>();

	if (IsLocallyControlled())
	{
		//** Local player begin play **//

		// Caches a reference to the radar subsytem
		RadarSubsystem = LocalPlayer->GetSubsystem<URadarSubsystem>();

		RadarSubsystem->SetPhysicalRadius(1500.0f);
	}
	else
	{
		//** Not local begin play **//


	}

	//** Authority begin play **//
	if (HasAuthority())
	{
		SetupPlayerCharacter();

	}
}

void AMasterCharacter::SetupPlayerCharacter()
{
	bool bIsLocal = IsLocallyControlled();

	//** General Player Character Setup **//

	// Gets a reference to the player state's inventory
	if (auto PS = Cast<AMatchPlayerState>(GetPlayerState()))
	{
		InventoryComponent = PS->InventoryComponent;
		InventoryComponent->SetOwningCharacter(this);
		InventoryComponent->OnSelectionUpdated.AddDynamic(this, &AMasterCharacter::OnInventorySelectionUpdated);
	}

	if (bIsLocal)
	{
		//** Local Player Character Setup **//


	}
	else
	{
		//** Not Local Player Character Setup **//
		const ETeamComparisonResult TeamComparisonResult = FactionsSessionSubsystem->CompareTeams(this, GetWorld()->GetFirstPlayerController());

		switch (TeamComparisonResult)
		{
		case ETeamComparisonResult::Equal:
			// TODO: Implement team mate radar icon and nametag

			RadarEntityComponent->PushIconSubclass(RadarTeammateIconClass);
			RadarEntityComponent->PushEntity();

			break;
		case ETeamComparisonResult::Different:
			// TODO: Implement enemy radar icon and nametag

			RadarEntityComponent->PushIconSubclass(RadarEnemyIconClass);
			RadarEntityComponent->PushEntity();

			break;
		case ETeamComparisonResult::Invalid:
		default:
			break;
		}

	}

	if (HasAuthority())
	{
		//** Authority Player Character Setup

	}

	// Notify blueprint classes
	OnSetupPlayerCharacter();
}

void AMasterCharacter::OnInventorySelectionUpdated(const int32 NewValue)
{
	if (IsLocallyControlled())
	{
		InventoryComponent->GetSelectionEquipment(NewValue)->SetSecondaryAction(IsAiming());
	}
}

void AMasterCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	SetupPlayerCharacter();
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

	if (InventoryComponent)
	{
		if (auto Equipment = InventoryComponent->GetCurrentEquipment())
		{
			Equipment->SetSecondaryAction(true);
		}
	}
}

void AMasterCharacter::InputAimReleased()
{
	InputData.bHoldingAim = false;

	if (InventoryComponent)
	{
		if (auto Equipment = InventoryComponent->GetCurrentEquipment())
		{
			Equipment->SetSecondaryAction(false);
		}
	}
}

void AMasterCharacter::InputFirePressed()
{
	InputData.bHoldingFire = true;

	if (InventoryComponent)
	{
		if (auto Equipment = InventoryComponent->GetCurrentEquipment())
		{
			Equipment->SetPrimaryAction(true);
		}
	}
}

void AMasterCharacter::InputFireReleased()
{
	InputData.bHoldingFire = false;

	if (InventoryComponent)
	{
		if (auto Equipment = InventoryComponent->GetCurrentEquipment())
		{
			Equipment->SetPrimaryAction(false);
		}
	}
}

void AMasterCharacter::InputSwitchShoulderPressed()
{
	InputData.bHoldingSwitchShoulder = true;

	if (IsAiming() && !InputData.bBlockShoulderSwitch)
	{
		const EShoulder NewShoulder = (Shoulder == EShoulder::Right ? EShoulder::Left : EShoulder::Right);
		SetShoulder(NewShoulder);

		InputData.bBlockShoulderSwitch = true;
		GetWorldTimerManager().SetTimer(ShoulderSwitchDelayHandle, this, &AMasterCharacter::InputCompleteShoulderSwitchDelay, SHOULDER_SWITCH_DELAY, false);
	}
}

void AMasterCharacter::InputSwitchShoulderReleased()
{
	InputData.bHoldingSwitchShoulder = true;
}

void AMasterCharacter::InputSelectRightPressed()
{
	if (InputData.bIsHotBarVisible)
	{
		InventoryComponent->OffsetHorizontalSelection(1);
	}
	else
	{
		InventoryComponent->SetSelection(2);
	}

	InputDisplayHotBar();
}

void AMasterCharacter::InputSelectLeftPressed()
{
	if (InputData.bIsHotBarVisible)
	{
		InventoryComponent->OffsetHorizontalSelection(-1);
	}
	else
	{
		InventoryComponent->SetSelection(1);
	}

	InputDisplayHotBar();
}

void AMasterCharacter::InputSelectUpPressed()
{
	if (InputData.bIsHotBarVisible)
	{
		InventoryComponent->OffsetVerticalSelection(-1);
	}
	else
	{
		InventoryComponent->SetSelection(6);
	}

	InputDisplayHotBar();
}

void AMasterCharacter::InputSelectDownPressed()
{
	if (InputData.bIsHotBarVisible)
	{
		InventoryComponent->OffsetVerticalSelection(1);
	}
	else
	{
		InventoryComponent->SetSelection(7);
	}

	InputDisplayHotBar();
}

void AMasterCharacter::InputCompleteShoulderSwitchDelay()
{
	InputData.bBlockShoulderSwitch = false;

	if (GetWorldTimerManager().IsTimerActive(ShoulderSwitchDelayHandle))
	{
		GetWorldTimerManager().ClearTimer(ShoulderSwitchDelayHandle);
	}
}

void AMasterCharacter::InputDisplayHotBar()
{
	InputData.bIsHotBarVisible = true;
	GetWorldTimerManager().SetTimer(HotBarVisibilityTimeHandle, this, &AMasterCharacter::InputHideHotBar, HOTBAR_VISIBILITY_TIME, false);
}

void AMasterCharacter::InputHideHotBar()
{
	InputData.bIsHotBarVisible = false;
}

float AMasterCharacter::GetSensitivityX() const
{
	return (IsAiming() ? SettingsSubsystem->SensitivityAimingX : SettingsSubsystem->SensitivityX);
}

float AMasterCharacter::GetSensitivityY() const
{
	return (IsAiming() ? SettingsSubsystem->SensitivityAimingY : SettingsSubsystem->SensitivityY);
}

// Called every frame
void AMasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//** General tick **//
	const bool bIsLocal = IsLocallyControlled();

	// Handles both character and movement states
	HandleCharacterState(DeltaTime, bIsLocal);
	HandleMovementState(DeltaTime, bIsLocal);

	// Handles camera updates
	HandleCamera(DeltaTime, bIsLocal);

	if (bIsLocal)
	{
		//** Local player tick **//

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
		//** Not local tick **//

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

	//** Bind axis input events **//
	PlayerInputComponent->BindAxis("MoveForward", this, &AMasterCharacter::InputMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMasterCharacter::InputMoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &AMasterCharacter::InputLookUp);
	PlayerInputComponent->BindAxis("LookRight", this, &AMasterCharacter::InputLookRight);

	//** Bind action input events **//
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMasterCharacter::InputSprintPressed);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMasterCharacter::InputSprintReleased);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMasterCharacter::InputCrouchPressed);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMasterCharacter::InputCrouchReleased);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AMasterCharacter::InputAimPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AMasterCharacter::InputAimReleased);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMasterCharacter::InputFirePressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AMasterCharacter::InputFireReleased);
	PlayerInputComponent->BindAction("SwitchShoulder", IE_Pressed, this, &AMasterCharacter::InputSwitchShoulderPressed);
	PlayerInputComponent->BindAction("SwitchShoulder", IE_Released, this, &AMasterCharacter::InputSwitchShoulderReleased);
	PlayerInputComponent->BindAction("SelectRight", IE_Pressed, this, &AMasterCharacter::InputSelectRightPressed);
	PlayerInputComponent->BindAction("SelectLeft", IE_Pressed, this, &AMasterCharacter::InputSelectLeftPressed);
	PlayerInputComponent->BindAction("SelectUp", IE_Pressed, this, &AMasterCharacter::InputSelectUpPressed);
	PlayerInputComponent->BindAction("SelectDown", IE_Pressed, this, &AMasterCharacter::InputSelectDownPressed);
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

void AMasterCharacter::DamageEntity(float Damage, AActor* DamageInstigator, AActor* Causer)
{
	HealthComponent->OffsetAttributeValue(Damage * -1.0f);
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
	const bool bIsLocal = IsLocallyControlled();

	switch (UpdatedCharacterState)
	{
	case ECharacterState::Default:

		// Default State update

		if (bState)
		{
			UpdateMovementState(MovementState, true);

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

		if (auto Equipment = InventoryComponent->GetCurrentEquipment())
		{
			Equipment->SetSecondaryAction(bState);
		}

		if (bState)
		{
			if (IsSprinting())
			{
				SetMovementState(EMovementState::Standing);
			}

			CameraData = AimingCameraData->Data;

			if (bIsLocal)
			{
				InputCompleteShoulderSwitchDelay();
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
	const float MovingSpeed = GetVelocity().Length();

	// Controls aiming input
	if (bIsLocal)
	{
		if (InputData.bHoldingAim)
		{
			if (!IsAiming())
			{
				SetCharacterState(ECharacterState::Aiming);
			}
		}
		else
		{
			if (IsAiming())
			{
				SetCharacterState(ECharacterState::Default);
			}
		}
	}

	// Resets shoulder to right shoulder if moving and not aiming
	if (Shoulder != EShoulder::Right && !IsAiming() && MovingSpeed >= MIN_SHOULDER_SWAP_SPED)
	{
		SetShoulder(EShoulder::Right);
	}
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

			if (!IsAiming())
			{
				CameraData = StandingCameraData->Data;
			}
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

			if (!IsAiming())
			{
				CameraData = CrouchingCameraData->Data;
			}
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

			CameraData = SprintingCameraData->Data;
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
			if (!IsSprinting() && MovingSpeed > MIN_SPRINTING_SPEED && StaminaComponent->GetPercent() >= 0.25f && !IsAiming())
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


		// Camera input
		AddControllerYawInput(InputData.LookRightValue * GetSensitivityX());
		AddControllerPitchInput(InputData.LookUpValue * GetSensitivityY());
		//...

		// Movement input
		FRotator InputRotation = GetControlRotation();
		InputRotation.Roll = 0.0f;
		InputRotation.Pitch = 0.0f;

		const FVector ForwardInputDirection = UKismetMathLibrary::GetForwardVector(InputRotation);
		const FVector RightInputDirection = UKismetMathLibrary::GetRightVector(InputRotation);

		AddMovementInput(ForwardInputDirection, InputData.MoveForwardValue);
		AddMovementInput(RightInputDirection, InputData.MoveRightValue);
		//...

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

void AMasterCharacter::HandleCamera(float DeltaTime, const bool bIsLocal)
{
	// NOTE
	// Camera updates are relevant for every client because of spectating

	//** Camera Updates from Character and Movement States **//
	const float CurrentDistance = CameraArm->TargetArmLength;
	const float CurrentFov = PlayerCamera->FieldOfView;
	const float SettingsFov = SettingsSubsystem->FOV;
	const float CurrentShoulderOffset = CameraArm->SocketOffset.Y;

	const float ShoulderOffsetMultiplier = (float)(((int)(Shoulder)) - 1);
	const float TargetShoulderOffset = CameraData.ShoulderOffset * ShoulderOffsetMultiplier;

	float UpdatedDistance = FMath::FInterpTo<float>(CurrentDistance, CameraData.Distance, DeltaTime, CameraData.DistanceInterpSpeed);
	float UpdatedFov = FMath::FInterpTo<float>(CurrentFov, SettingsFov + CameraData.FovOffset, DeltaTime, CameraData.FovOffsetInterpSped);
	float UpdatedShoulderOffset = FMath::FInterpTo<float>(CurrentShoulderOffset, TargetShoulderOffset, DeltaTime, CameraData.ShoudlerOffsetInterpSpeed);
	
	//CameraArm->TargetArmLength = UpdatedDistance;
	PlayerCamera->SetFieldOfView(UpdatedFov);
	CameraArm->SocketOffset.Y = UpdatedShoulderOffset;

	//** General Camera Updates **//

	// Test spring arm collision
	FHitResult HitResult(ForceInit);
	FCollisionShape Shape = FCollisionShape::MakeSphere(CameraArm->ProbeSize * 2.0f);
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	const FVector StartLocation = CameraArm->GetComponentLocation();
	const FVector EndLocation = CameraArm->GetSocketLocation(CameraArm->SocketName);
	//GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, CameraArm->ProbeChannel, CollisionParams);
	GetWorld()->SweepSingleByChannel(HitResult, StartLocation, EndLocation, FQuat::Identity, CameraArm->ProbeChannel, Shape, CollisionParams);

	if (HitResult.bBlockingHit)
	{
		const float BlockDistance = FVector::Distance(StartLocation, HitResult.ImpactPoint);
		const float InterpSpeed = (BlockDistance >= CurrentDistance ? FreeCameraInterpSpeed : BlockedCameraInterpSpeed);
		UpdatedDistance = FMath::FInterpTo(CameraArm->TargetArmLength, BlockDistance, DeltaTime, InterpSpeed);
	}

	CameraArm->TargetArmLength = UpdatedDistance;

	// Update follow location
	const FVector CurrentCameraLocation = CameraArm->GetComponentLocation();
	const FVector TargetCameraLocation = GetActorLocation() + FVector(0.0f, 0.0f, CAMERA_HEIGHT);
	const FVector UpdatedCameraLocation = FMath::VInterpTo(CurrentCameraLocation, TargetCameraLocation, DeltaTime, CameraData.FollowSpeed);
	CameraArm->SetWorldLocation(UpdatedCameraLocation);
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
