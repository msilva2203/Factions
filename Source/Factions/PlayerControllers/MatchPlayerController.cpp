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

	if (IsLocalController())
	{
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
		FInputActionBinding CurBinding;

		// Bind action events
		CurBinding = InputComponent->BindAction("Spectate Camera", IE_Pressed, this, &AMatchPlayerController::InputSpectateCamera);
		CurBinding.bConsumeInput = false;
		CurBinding = InputComponent->BindAction("Spectate Player", IE_Pressed, this, &AMatchPlayerController::InputSpectatePlayer);
		CurBinding.bConsumeInput = false;
		CurBinding = InputComponent->BindAction("Show Scoreboard", IE_Pressed, this, &AMatchPlayerController::InputShowScoreboard);
		CurBinding.bConsumeInput = false;
	}
}

void AMatchPlayerController::SetupPlayerController()
{
	Super::SetupPlayerController();

	if (IsLocalController())
	{
		// Creates game HUD and scoreboard
		UserInterfaceSubsystem->PushHUD(GameModeHUDClass, true);
		UserInterfaceSubsystem->PushHUD(MainHUDClass, true);
		UserInterfaceSubsystem->PushHUD(ScoreboardClass, true);
	}

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

		if (IsLocalController())
		{
			UBaseHUD* MainHUD = UserInterfaceSubsystem->GetHUD(MainHUDClass);

			SetInputMode(FInputModeGameOnly());
			bShowMouseCursor = false;

			if (!ArenaCameras.IsEmpty())
			{
				SpectateCamera(ArenaCameras[SpectatingCameraIndex]);
			}

			if (MainHUD)
			{
				UserInterfaceSubsystem->HideHUD(MainHUD, true);
			}
		}

		break;
	case EPlayerMatchState::Playing:

		if (IsLocalController())
		{
			UBaseHUD* MainHUD = UserInterfaceSubsystem->GetHUD(MainHUDClass);

			SetInputMode(FInputModeGameOnly());
			bShowMouseCursor = false;

			if (MainHUD)
			{
				UserInterfaceSubsystem->DisplayHUD(MainHUD, true);
			}
		}

		break;
	default:
		break;
	}

	// Notify blueprint classes
	OnPlayerMatchStateUpdated(NewValue);
}

void AMatchPlayerController::player_set_material(EMaterial Material, int32 NewValue)
{
	if (auto PlayerS = GetPlayerState<AMatchPlayerState>())
	{
		if (PlayerS->InventoryComponent)
		{
			PlayerS->InventoryComponent->SetMaterialCount(Material, NewValue);
		}
	}
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

void AMatchPlayerController::InputShowScoreboard()
{
	UBaseHUD* Scoreboard = UserInterfaceSubsystem->GetHUD(ScoreboardClass);
	UserInterfaceSubsystem->ToggleHUD(Scoreboard, false);
}
