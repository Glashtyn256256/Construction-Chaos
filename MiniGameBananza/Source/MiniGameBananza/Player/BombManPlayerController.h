// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ScriptDelegates.h"
#include "Actor.h"
#include "BombManPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABombManPlayerController();

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void OnHit(AActor* ActorToDestroy, ABombManPlayerController* DamageCauser);
	void StartRespawning();

protected:

private:
	
	void Respawn();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float MaxRespawnTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float RespawnModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	int NumLives = 3.0;

private:
	float TimeUntilRespawn;
	bool bIsRespawning;
	
};
