// Developed by the Factions community


#include "Factions/Subsystems/FactionsSessionSubsystem.h"

#include "Factions/PlayerControllers/MasterPlayerController.h"
#include "Factions/GameStates/MasterGameState.h"
#include "Factions/Components/EntityAttributeComponent.h"
#include "Factions/PlayerStates/MatchPlayerState.h"

DEFINE_LOG_CATEGORY(FactionsSessionLog);

void UFactionsSessionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UFactionsSessionSubsystem::AddSessionPlayerState(AMasterPlayerState* AddedPlayerState)
{
	UE_LOG(FactionsSessionLog, Warning, TEXT("Adding player to session subsystem"));

	if (!SessionPlayerStates.Contains(AddedPlayerState))
	{
		SessionPlayerStates.Add(AddedPlayerState);
		OnPlayerAdded.Broadcast(AddedPlayerState);

		UE_LOG(FactionsSessionLog, Warning, TEXT("Broadcasting player added to factions subsystem"));
	}
}

void UFactionsSessionSubsystem::RemoveSessionPlayerState(AMasterPlayerState* RemovedPlayerState)
{
	UE_LOG(FactionsSessionLog, Warning, TEXT("Removing player to session subsystem"));

	if (SessionPlayerStates.Contains(RemovedPlayerState))
	{
		SessionPlayerStates.Remove(RemovedPlayerState);
		OnPlayerRemoved.Broadcast(RemovedPlayerState);

		UE_LOG(FactionsSessionLog, Warning, TEXT("Broadcasting player removed to factions subsystem"));
	}
}

ETeamComparisonResult UFactionsSessionSubsystem::CompareTeams(AActor* A, AActor* B)
{
	IFactionsEntityInterface* InterfaceA = Cast<IFactionsEntityInterface>(A);
	IFactionsEntityInterface* InterfaceB = Cast<IFactionsEntityInterface>(B);

	if (InterfaceA && InterfaceB)
	{
		if (InterfaceA->GetEntityTeam() == InterfaceB->GetEntityTeam())
			return ETeamComparisonResult::Equal;
		return ETeamComparisonResult::Different;
	}
	return ETeamComparisonResult::Invalid;
}

EFactionsTeam UFactionsSessionSubsystem::GetEntityTeam(AActor* Entity)
{
	if (auto Interface = Cast<IFactionsEntityInterface>(Entity))
	{
		return Interface->GetEntityTeam();
	}
	return EFactionsTeam::None;
}

void UFactionsSessionSubsystem::RegisterPlayersInSession()
{
	SessionPlayersData.Empty();
	auto Players = GetWorld()->GetGameState()->PlayerArray;

	for (auto& Player : Players)
	{
		FSessionPlayerData NewData;
		NewData.PlayerNetId = Player->GetUniqueId().GetUniqueNetId();
		NewData.Team = GetEntityTeam(Player);

		SessionPlayersData.Add(NewData);
	}
}

bool UFactionsSessionSubsystem::GetSessionPlayerData(AMasterPlayerState* Player, FSessionPlayerData& SessionPlayerData)
{
	if (!SessionPlayersData.IsEmpty())
	{
		for (auto& Data : SessionPlayersData)
		{
			auto NetId = Player->GetUniqueId().GetUniqueNetId();

			if (NetId == Data.PlayerNetId)
			{
				SessionPlayerData = Data;
				return true;
			}
		}
	}
	return false;
}

void UFactionsSessionSubsystem::SetSessionGameMode(const EFactionsGameMode NewGameMode)
{
	SessionGameMode = NewGameMode;
	OnSessionGameModeUpdated.Broadcast(SessionGameMode);
}

void UFactionsSessionSubsystem::DamageEntity(AActor* Entity, float Damage, AActor* Instigator, AActor* Causer)
{
	if (auto Interface = Cast<IFactionsEntityInterface>(Entity))
	{
		Interface->DamageEntity(Damage, Instigator, Causer);
	}
}

bool UFactionsSessionSubsystem::IsEntityDead(AActor* Entity)
{
	if (auto Interface = Cast<IFactionsEntityInterface>(Entity))
	{
		return Interface->IsEntityDead();
	}
	return false;
}

void UFactionsSessionSubsystem::RewardEntity(AActor* Entity, const ERewardAction RewardAction)
{
	if (auto PS = Cast<AMatchPlayerState>(Entity))
	{
		PS->AddReward(RewardAction);
	}
}
