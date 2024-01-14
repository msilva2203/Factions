// Developed by the Factions community

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"

#include "ArenaCamera.generated.h"

UCLASS()
class FACTIONS_API AArenaCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArenaCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Arena Camera")
	void Spectate(APlayerController* Player);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena Camera")
	UCameraComponent* CameraComponent;

};
