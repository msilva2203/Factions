// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "Factions/GameModes/MasterGameMode.h"

#include "MatchGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FACTIONS_API AMatchGameMode : public AMasterGameMode
{
	GENERATED_BODY()
	
public:
	virtual void PlayerPostLogin(AMasterPlayerController* PlayerController) override;
	virtual void PlayerLogout(AMasterPlayerController* PlayerController) override;


};
