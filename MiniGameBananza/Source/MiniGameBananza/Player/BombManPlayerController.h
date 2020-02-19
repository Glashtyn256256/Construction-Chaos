// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGamePlayerController.h"
#include "BombManPlayerCharacter.h"
#include "BombManPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPlayerController : public AMiniGamePlayerController
{
	GENERATED_BODY()

#pragma region Functions
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	inline void StartRespawnProcess();
private:
	void Respawn();
#pragma endregion

#pragma region Variables
public:
	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float MaxRespawnTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float RespawnCountdownModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	int NumLives = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	TSubclassOf<ABombManPlayerCharacter> PlayerCharacterToSpawn;

private:
	float RespawnCountdownTimer;
	bool bIsRespawning;
#pragma endregion
	
};
