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
			Super::OnPowerupEnd();
		}
	}
}

void ABombManPowerupMovementBoost::OnPowerupStart(ABombManPlayerCharacter* Character)
{
	Super::OnPowerupStart(Character);

	Time = 0.0f;

	if (Character)
	{
		Character->SetPlayerMovementSpeed(PlayerMovementSpeed);
	}
}

void ABombManPowerupMovementBoost::OnPowerupEnd(ABombManPlayerCharacter* Character)
{
	Super::OnPowerupEnd(Character);

	if (Character)
	{
		Character->ResetPlayerMovementSpeed();
	}
}