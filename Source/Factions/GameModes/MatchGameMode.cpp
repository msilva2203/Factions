// Developed by the Factions community


#include "Factions/GameModes/MatchGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Factions/PlayerControllers/MatchPlayerController.h"
#include "Factions/PlayerStates/MatchPlayerState.h"
#include "Factions/GameStates/MatchGameState.h"

AMatchGameMode::AMatchGameMode(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	GameStateClass = AMatchGameState::StaticClass();
	PlayerStateClass = AMatchPlayerState::StaticClass();
	PlayerControllerClass = AMatchPlayerController::StaticClass();
}

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (auto MatchGameState = GetGameState<AMatchGameState>())
	{
		MatchGameState->OnGameTimeUpdate.AddDynamic(this, &AMatchGameMode::OnGameTimeUpdate);
	}

	TArray<AActor*> SpawnerActors;
	UGameplayStatics::GetAllActorsOfClass(this, APlayerSpawner::StaticClass(), SpawnerActors);

	for (auto Actor : SpawnerActors)
	{
		if (auto Spawner = Cast<APlayerSpawner>(Actor))
		{
			if (Spawner->bIsStartSpawner)
			{
				StartSpawners.Add(Spawner);
			}
			else
			{
				PlayerSpawners.Add(Spawner);
			}
		}
	}
}

void AMatchGameMode::Start()
{
	Super::Start();

	StartPlayers();

	if (auto MatchGameState = GetGameState<AMatchGameState>())
	{
		MatchGameState->SetInProgress(true);
	}
}

void AMatchGameMode::StartPlayers()
{
	for (auto Player : ConnectedPlayers)
	{
		for (auto Spawner : StartSpawners)
		{
			if (Spawner->IsAvailable())
			{
				const ETeamComparisonResult CompResult = FactionsSessionSubsystem->CompareTeams(Player, Spawner);
				if (CompResult == ETeamComparisonResult::Equal)
				{
					UE_LOG(LogTemp, Warning, TEXT("Starting player"));
					Spawner->SpawnPlayer(Player);
					if (auto PS = Player->GetPlayerState<AMatchPlayerState>())
					{
						PS->InventoryComponent->ResetInventory();
					}
					break;
				}
			}
		}
	}
}

bool AMatchGameMode::CanPlayerRespawn(AMasterPlayerController* Player) const
{
	return true;
}

void AMatchGameMode::RespawnPlayer(AMasterPlayerController* Player)
{
	UE_LOG(LogTemp, Warning, TEXT("Respawning player"));
	FindPlayerSpawner(Player)->SpawnPlayer(Player);
	if (auto PS = Player->GetPlayerState<AMatchPlayerState>())
	{
		PS->InventoryComponent->ResetWeapons();
	}
}

APlayerSpawner* AMatchGameMode::FindPlayerSpawner(AMasterPlayerController* Player)
{
	// TODO: Implement spawner finding algorithm
	for (auto Spawner : PlayerSpawners)
	{
		if (Spawner->IsAvailable())
		{
			const ETeamComparisonResult CompResult = FactionsSessionSubsystem->CompareTeams(Spawner, Player);
			if (CompResult == ETeamComparisonResult::Equal)
			{
				return Spawner;
			}
		}
	}
	return nullptr;
}

void AMatchGameMode::AssignTeamToPlayer(AMasterPlayerState* Player)
{
	const int32 Team1Size = GetTeamSize(EFactionsTeam::Team01);
	const int32 Team2Size = GetTeamSize(EFactionsTeam::Team02);

	const EFactionsTeam NewTeam = (Team1Size > Team2Size ? EFactionsTeam::Team02 : EFactionsTeam::Team01);
	Player->SetPlayerTeam(NewTeam);
}

void AMatchGameMode::OnGameTimeUpdate(int32 Time)
{
	// Respawn wave of dead players
	// TODO: Implement wave time abstraction

	if (bStarted && Time % 20 == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Time: %d"), Time);
		for (auto Player : ConnectedPlayers)
		{
			if (CanPlayerRespawn(Player) && FactionsSessionSubsystem->IsEntityDead(Player))
			{
				RespawnPlayer(Player);
			}
		}
	}
}

void AMatchGameMode::PlayerPostLogin(AMasterPlayerController* PlayerController)
{
	Super::PlayerPostLogin(PlayerController);

	if (auto PS = PlayerController->GetPlayerState<AMatchPlayerState>())
	{
		PS->SetPlayerMatchState(EPlayerMatchState::Spectating);

		// Assigns new team if team is not set
		if (PS->PlayerTeam == EFactionsTeam::None)
		{
			AssignTeamToPlayer(PS);
		}
	}
}

void AMatchGameMode::PlayerLogout(AMasterPlayerController* PlayerController)
{
	Super::PlayerLogout(PlayerController);

}

void AMatchGameMode::gm_update_timeremaining(const int32 Time)
{
	if (auto MatchGameState = GetGameState<AMatchGameState>())
	{
		MatchGameState->SetRemainingTime(Time, true);
	}
}
