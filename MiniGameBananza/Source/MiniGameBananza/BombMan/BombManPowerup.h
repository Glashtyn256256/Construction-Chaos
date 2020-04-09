// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/BombMan/BombManCollision.h"
#include "BombManPowerup.generated.h"

class ABombManPlayerCharacter;
/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPowerup : public ABombManCollision
{
	GENERATED_BODY()
	
public:
	virtual void OnPlayerCollision(ABombManPlayerCharacter* Character) override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void PowerupStart(ABombManPlayerCharacter* Character);
	virtual void PowerupEnd(ABombManPlayerCharacter* Character);
	void PowerupEnd();

protected:
	ABombManPlayerCharacter* PowerupCharacter;
	bool bPowerupActive;
};
