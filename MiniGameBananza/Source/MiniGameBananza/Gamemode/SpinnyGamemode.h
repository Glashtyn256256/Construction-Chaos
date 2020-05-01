// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/Spinny/SpinnyPole.h"
#include "MiniGameBananza/Gamemode/MiniGameBananzaGameModeBase.h"
#include "SpinnyGamemode.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ASpinnyGamemode : public AMiniGameBananzaGameModeBase
{
	GENERATED_BODY()
public:
	ASpinnyGamemode();

public:
	virtual void Tick(float DeltaTime) override;

	int GetSpeedLevel() const;

	bool PoleIsFast() const;

private:
	void IncrementSpeedLevel();

public:
	UPROPERTY(EditDefaultsOnly)
	int SpeedPerLevelIncrement = 15.0f;

private:
	ASpinnyPole* SpinnyPole;
	int SpeedLevel;

};
