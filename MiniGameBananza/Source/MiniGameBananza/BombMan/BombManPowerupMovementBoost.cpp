// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPowerupMovementBoost.h"
#include "MiniGameBananza/Player/BombManPlayerCharacter.h"

void ABombManPowerupMovementBoost::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bPowerupActive)
	{
		Time += DeltaTime;

		if (Time >= PowerupTime)
		{
			Time = 0.0f;
			Super::PowerupEnd();
		}
	}
}

void ABombManPowerupMovementBoost::PowerupStart(ABombManPlayerCharacter* Character)
{
	Super::PowerupStart(Character);

	Time = 0.0f;

	if (Character)
	{
		Character->SetPlayerMovementSpeed(PlayerMovementSpeed);
	}
}

void ABombManPowerupMovementBoost::PowerupEnd(ABombManPlayerCharacter* Character)
{
	Super::PowerupEnd(Character);

	if (Character)
	{
		Character->ResetPlayerMovementSpeed();
	}
}