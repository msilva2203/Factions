// Developed by the Factions community


#include "Factions/Subsystems/FactionsSessionSubsystem.h"
#include "FactionsSessionSubsystem.h"

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
