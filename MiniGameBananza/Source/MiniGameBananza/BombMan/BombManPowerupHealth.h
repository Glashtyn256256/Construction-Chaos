// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/BombMan/BombManPowerup.h"
#include "BombManPowerupHealth.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPowerupHealth : public ABombManPowerup
{
	GENERATED_BODY()
	
protected:
	virtual void PowerupStart(ABombManPlayerCharacter* Character) override;
	virtual void PowerupEnd(ABombManPlayerCharacter* Character) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Powerup")
	int Lives = 1;
};
