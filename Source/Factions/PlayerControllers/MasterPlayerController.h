// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"
#include "Factions/Interfaces/FactionsEntityInterface.h"

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

	virtual EFactionsTeam GetEntityTeam() override;

	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Master Player Controller")
	void Server_SetPlayerTeam(const EFactionsTeam NewTeam);
	void Server_SetPlayerTeam_Implementation(const EFactionsTeam NewTeam);
	bool Server_SetPlayerTeam_Validate(const EFactionsTeam NewTeam);
};
