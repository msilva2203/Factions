// Developed by the Factions community


#include "Factions/GameModes/MasterGameMode.h"

#include "Factions/GameStates/MasterGameState.h"
#include "Factions/PlayerControllers/MasterPlayerController.h"
#include "Factions/PlayerStates/MasterPlayerState.h"

AMasterGameMode::AMasterGameMode(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	bStarted(false)
{
	GameStateClass = AMasterGameState::StaticClass();
	PlayerControllerClass = AMasterPlayerController::StaticClass();
	PlayerStateClass = AMasterPlayerState::StaticClass();

	DefaultPlayerName = FText::FromName(TEXT("FACTIONS PLAYER"));
}

void AMasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Chaches a reference to the factions session subsytem
	FactionsSessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();

}

void AMasterGameMode::Start()
{
	bStarted = true;
	OnStart();
}

void AMasterGameMode::PostLogin(APlayerController* PlayerController)
{
	Super::OnPostLogin(PlayerController);

	if (auto Player = Cast<AMasterPlayerController>(PlayerController))
	{
		ConnectedPlayers.Add(Player);
		PlayerPostLogin(Player);
	}
}

void AMasterGameMode::HandleStartingNewPlayer_Implementation(APlayerController* PlayerController)
{
	Super::HandleStartingNewPlayer_Implementation(PlayerController);

}

void AMasterGameMode::Logout(AController* Controller)
{
	Super::Logout(Controller);

	if (auto Player = Cast<AMasterPlayerController>(Controller))
	{
		ConnectedPlayers.Remove(Player);
		PlayerLogout(Player);
	}
}

void AMasterGameMode::PlayerPostLogin(AMasterPlayerController* PlayerController)
{
	if (FactionsSessionSubsystem)
	{
		if (auto PlayerState = PlayerController->GetPlayerState<AMasterPlayerState>())
		{
			FSessionPlayerData SessionPlayerData;
			if (FactionsSessionSubsystem->GetSessionPlayerData(PlayerState, SessionPlayerData))
			{
				PlayerState->SetPlayerTeam(SessionPlayerData.Team);
			}
		}
	}
	
}

void AMasterGameMode::PlayerLogout(AMasterPlayerController* PlayerController)
{

}

int32 AMasterGameMode::GetTeamSize(const EFactionsTeam Team)
{
	int32 Count = 0;
	for (auto Player : ConnectedPlayers)
	{
		const auto PlayerTeam = FactionsSessionSubsystem->GetEntityTeam(Player);
		if (PlayerTeam == Team)
			Count++;
	}
	return Count;
}

void AMasterGameMode::gm_start()
{
	Start();
}


