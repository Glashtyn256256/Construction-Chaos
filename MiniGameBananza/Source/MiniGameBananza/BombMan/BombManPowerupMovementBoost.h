// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/BombMan/BombManPowerup.h"
#include "BombManPowerupMovementBoost.generated.h"

class ABombManPlayerCharacter;

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPowerupMovementBoost : public ABombManPowerup
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnPowerupStart(ABombManPlayerCharacter* Character) override;
	virtual void OnPowerupEnd(ABombManPlayerCharacter* Character) override;

protected:
	float Time;

	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
	float PowerupTime = 3.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
	float PlayerMovementSpeed = 1000.0f;
	
};
