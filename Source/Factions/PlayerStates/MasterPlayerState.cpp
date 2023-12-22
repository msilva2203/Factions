// Developed by the Factions community


#include "Factions/PlayerStates/MasterPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Factions/Subsystems/FactionsSessionSubsystem.h"

AMasterPlayerState::AMasterPlayerState() :
	bArrived(false)
{
}

void AMasterPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Enables variable replication
	DOREPLIFETIME(AMasterPlayerState, PlayerTeam);
}

void AMasterPlayerState::BeginPlay()
{
	Super::BeginPlay();
	/**
	* Adds itself to the factions session subsystem
	*/
	auto SessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();
	SessionSubsystem->AddSessionPlayerState(this);

}

void AMasterPlayerState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	/**
	* Removes itself from the factions session subsystem
	*/
	auto SessionSubsystem = GetGameInstance()->GetSubsystem<UFactionsSessionSubsystem>();
	SessionSubsystem->RemoveSessionPlayerState(this);

}

void AMasterPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();

	bArrived = true;
	OnPlayerArrived.Broadcast();
}

EFactionsTeam AMasterPlayerState::GetEntityTeam()
{
	return PlayerTeam;
}

void AMasterPlayerState::OnRep_PlayerTeam()
{

}
