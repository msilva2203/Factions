// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Factions/Interfaces/FactionsEntityInterface.h"
#include "Factions/Subsystems/SettingsSubsystem.h"

#include "MasterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AMasterPlayerController : public APlayerController, public IFactionsEntityInterface
{
	GENERATED_BODY()
	
public:
	AMasterPlayerController();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Master Player Controller")
	void OnSetupPlayerController();

	UFUNCTION()
	virtual void SetupPlayerController();

	virtual void OnRep_PlayerState() override;

	virtual EFactionsTeam GetEntityTeam() override;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Master Player Controller")
	void Server_SetPlayerTeam(const EFactionsTeam NewTeam);
	void Server_SetPlayerTeam_Implementation(const EFactionsTeam NewTeam);
	bool Server_SetPlayerTeam_Validate(const EFactionsTeam NewTeam);

	UPROPERTY(BlueprintReadOnly, Category = "Master Player Controller")
	USettingsSubsystem* SettingsSubsystem;

	UFUNCTION(Exec, Category = "Master Player Controller")
	void player_set_fov(const float NewValue);

	UFUNCTION(Exec, Category = "Master Player Controller")
	void player_set_sensitivity_x(const float NewValue);

	UFUNCTION(Exec, Category = "Master Player Controller")
	void player_set_sensitivity_y(const float NewValue);

	UFUNCTION(Exec, Category = "Master Player Controller")
	void player_set_sensitivity_aiming_x(const float NewValue);

	UFUNCTION(Exec, Category = "Master Player Controller")
	void player_set_sensitivity_aiming_y(const float NewValue);
};
