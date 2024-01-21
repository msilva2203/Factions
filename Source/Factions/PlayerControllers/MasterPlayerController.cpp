// Developed by the Factions community


#include "Factions/PlayerControllers/MasterPlayerController.h"

#include "GameFramework/PlayerState.h"
#include "Factions/PlayerStates/MasterPlayerState.h"

AMasterPlayerController::AMasterPlayerController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{
	NetDormancy = ENetDormancy::DORM_DormantAll;
	NetUpdateFrequency = 0.0f;
}

void AMasterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetupPlayerController();
	}
}

void AMasterPlayerController::SetupPlayerController()
{
	// Notify blueprint classes
	OnSetupPlayerController();
}

void AMasterPlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	SetupPlayerController();
}

EFactionsTeam AMasterPlayerController::GetEntityTeam()
{
	IFactionsEntityInterface* Interface = Cast<IFactionsEntityInterface>(GetPlayerState<APlayerState>());
	if (Interface)
	{
		return Interface->GetEntityTeam();
	}
	return EFactionsTeam::None;
}

bool AMasterPlayerController::IsEntityDead() const
{
	return true;
}

void AMasterPlayerController::Server_SetPlayerTeam_Implementation(const EFactionsTeam NewTeam)
{
	GetPlayerState<AMasterPlayerState>()->SetPlayerTeam(NewTeam);
}

bool AMasterPlayerController::Server_SetPlayerTeam_Validate(const EFactionsTeam NewTeam)
{
	// Implement RPC validation
	return true;
}

void AMasterPlayerController::player_set_fov(const float NewValue)
{
	SettingsSubsystem = GetLocalPlayer()->GetSubsystem<USettingsSubsystem>();
	SettingsSubsystem->FOV = NewValue;
}

void AMasterPlayerController::player_set_sensitivity_x(const float NewValue)
{
	SettingsSubsystem = GetLocalPlayer()->GetSubsystem<USettingsSubsystem>();
	SettingsSubsystem->SensitivityX = NewValue;
}

void AMasterPlayerController::player_set_sensitivity_y(const float NewValue)
{
	SettingsSubsystem = GetLocalPlayer()->GetSubsystem<USettingsSubsystem>();
	SettingsSubsystem->SensitivityY = NewValue;
}

void AMasterPlayerController::player_set_sensitivity_aiming_x(const float NewValue)
{
	SettingsSubsystem = GetLocalPlayer()->GetSubsystem<USettingsSubsystem>();
	SettingsSubsystem->SensitivityAimingX = NewValue;
}

void AMasterPlayerController::player_set_sensitivity_aiming_y(const float NewValue)
{
	SettingsSubsystem = GetLocalPlayer()->GetSubsystem<USettingsSubsystem>();
	SettingsSubsystem->SensitivityAimingY = NewValue;
}
