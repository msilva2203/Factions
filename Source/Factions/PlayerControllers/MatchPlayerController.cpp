// Developed by the Factions community


#include "Factions/PlayerControllers/MatchPlayerController.h"
#include "Kismet/GameplayStatics.h"


AMatchPlayerController::AMatchPlayerController()
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
		PS->OnPlayerMatchStateUpdated.AddDynamic(this, &AMatchPlayerController::PlayerMatchStateUpdated);
	}
}

void AMatchPlayerController::OnPossess(APawn* InPawn)
{
	if (auto PS = GetPlayerState<AMatchPlayerState>())
	{
		PS->SetPlayerMatchState(EPlayerMatchState::Playing);
	}

	if (PreviousPawn)
	{
		PreviousPawn->K2_DestroyActor();
	}
	PreviousPawn = InPawn;
}

void AMatchPlayerController::OnUnPossess()
{
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
	if (PlayerMatchState == EPlayerMatchState::Spectating)
	{

	}
}

void AMatchPlayerController::InputSpectatePlayer()
{
	if (PlayerMatchState == EPlayerMatchState::Spectating)
	{

	}
}
