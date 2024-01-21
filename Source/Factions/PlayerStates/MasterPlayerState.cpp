// Developed by the Factions community


#include "Factions/PlayerStates/MasterPlayerState.h"

#include "Net/UnrealNetwork.h"
#include "Factions/Subsystems/FactionsSessionSubsystem.h"

AMasterPlayerState::AMasterPlayerState(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer),
	bArrived(false)
{
	NetDormancy = ENetDormancy::DORM_DormantAll;
	NetUpdateFrequency = 0.0f;
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

void AMasterPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if (auto PS = Cast<AMasterPlayerState>(PlayerState))
	{
		PS->PlayerTeam = PlayerTeam;
	}
}

void AMasterPlayerState::OnRep_PlayerName()
{
	Super::OnRep_PlayerName();

	bArrived = true;
	OnPlayerArrived.Broadcast(this);
}

EFactionsTeam AMasterPlayerState::GetEntityTeam()
{
	return PlayerTeam;
}

void AMasterPlayerState::SetPlayerTeam(const EFactionsTeam NewTeam)
{
	if (GetNetMode() < NM_Client)
	{
		if (PlayerTeam != NewTeam)
		{
			PlayerTeam = NewTeam;
			OnRep_PlayerTeam();
			ForceNetUpdate();
		}
	}
}

void AMasterPlayerState::OnRep_PlayerTeam()
{
	OnPlayerTeamUpdated.Broadcast(PlayerTeam);
}
