// Developed by the Factions community


#include "Factions/PlayerControllers/MatchPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Factions/Pawns/MasterCharacter.h"


AMatchPlayerController::AMatchPlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{

}

void AMatchPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Gets a reference to all arena cameras in the map
	TArray<AActor*> ArenaCameraActors;
	UGameplayStatics::GetAllActorsOfClass(this, AArenaCamera::StaticClass(), ArenaCameraActors);
	for (auto Actor : ArenaCameraActors)
	{
		if (auto Camera = Cast<AArenaCamera>(Actor))
		{
			ArenaCameras.Add(Camera);
		}
	}

}

void AMatchPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AMatchPlayerController::IsEntityDead() const
{
	if (auto PS = GetPlayerState<AMatchPlayerState>())
	{
		return PS->IsEntityDead();
	}
	return false;
}

void AMatchPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		// Bind action events
		InputComponent->BindAction("Spectate Camera", IE_Pressed, this, &AMatchPlayerController::InputSpectateCamera);
		InputComponent->BindAction("Spectate Player", IE_Pressed, this, &AMatchPlayerController::InputSpectatePlayer);
	}
}

void AMatchPlayerController::SetupPlayerController()
{
	Super::SetupPlayerController();

	if (auto PS = GetPlayerState<AMatchPlayerState>())
	{
		OnPlayerStateReplicated.Broadcast(PS);

		PS->OnPlayerMatchStateUpdated.AddDynamic(this, &AMatchPlayerController::PlayerMatchStateUpdated);
		PlayerMatchStateUpdated(PS->PlayerMatchState);
	}
}

void AMatchPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (auto NewCharacter = Cast<AMasterCharacter>(InPawn))
	{
		if (auto PS = GetPlayerState<AMatchPlayerState>())
		{
			PS->SetPlayerMatchState(EPlayerMatchState::Playing);
		}
	}
	else
	{
		UnPossess();
	}

	if (PreviousPawn)
	{
		PreviousPawn->K2_DestroyActor();
	}
	PreviousPawn = InPawn;
}

void AMatchPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
}

bool AMatchPlayerController::IsSpectating() const
{
	return PlayerMatchState == EPlayerMatchState::Spectating;
}

void AMatchPlayerController::SpectateCamera(AArenaCamera* Camera)
{
	if (IsSpectating())
	{
		Camera->Spectate(this);
		ArenaCameras.Find(Camera, SpectatingCameraIndex);
	}
}

void AMatchPlayerController::PlayerMatchStateUpdated(const EPlayerMatchState NewValue)
{
	PlayerMatchState = NewValue;

	switch (NewValue)
	{
	case EPlayerMatchState::None:
		break;
	case EPlayerMatchState::Loading:
		break;
	case EPlayerMatchState::Spectating:

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;

		if (!ArenaCameras.IsEmpty())
		{
			SpectateCamera(ArenaCameras[SpectatingCameraIndex]);
		}

		break;
	case EPlayerMatchState::Playing:

		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;

		break;
	default:
		break;
	}

	// Notify blueprint classes
	OnPlayerMatchStateUpdated(NewValue);
}

void AMatchPlayerController::InputSpectateCamera()
{
	if (IsSpectating())
	{
		SpectatingCameraIndex++;
		if (SpectatingCameraIndex >= ArenaCameras.Num())
		{
			SpectatingCameraIndex = 0;
		}

		if (!ArenaCameras.IsEmpty())
		{
			SpectateCamera(ArenaCameras[SpectatingCameraIndex]);
		}
	}
}

void AMatchPlayerController::InputSpectatePlayer()
{
	if (IsSpectating())
	{

	}
}
