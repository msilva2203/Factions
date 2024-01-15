// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "UObject/Interface.h"
#include "Factions/Factions.h"

#include "FactionsEntityInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFactionsEntityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FACTIONS_API IFactionsEntityInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual EFactionsTeam GetEntityTeam();
	virtual void DamageEntity(float Damage, AActor* DamageInstigator, AActor* Causer);
};
