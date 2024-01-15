// Developed by the Factions community


#include "Factions/GameModes/MatchGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Factions/PlayerControllers/MasterPlayerController.h"
#include "Factions/PlayerStates/MatchPlayerState.h"

AMatchGameMode::AMatchGameMode(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{

}

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();

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
}

void AMatchGameMode::StartPlayers()
{
	for (auto Player : ConnectedPlayers)
	{
		for (auto Spawner : StartSpawners)
		{
			if (Spawner->IsAvailable())
			{
				ETeamComparisonResult CompResult = FactionsSessionSubsystem->CompareTeams(Player, Spawner);
				
				if (CompResult == ETeamComparisonResult::Equal)
				{
					Spawner->SpawnPlayer(Player);
				}
			}
		}
	}
}

APlayerSpawner* AMatchGameMode::FindPlayerSpawner(AMasterPlayerController* Player)
{
	// TODO: Implement spawner finding algorithm
	return nullptr;
}

void AMatchGameMode::AssignTeamToPlayer(AMasterPlayerState* Player)
{
	const int32 Team1Size = GetTeamSize(EFactionsTeam::Team01);
	const int32 Team2Size = GetTeamSize(EFactionsTeam::Team02);

	const EFactionsTeam NewTeam = (Team1Size > Team2Size ? EFactionsTeam::Team02 : EFactionsTeam::Team01);
	Player->SetPlayerTeam(NewTeam);
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
