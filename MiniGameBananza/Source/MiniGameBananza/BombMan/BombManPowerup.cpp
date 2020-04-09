// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPowerup.h"
#include "MiniGameBananza/Player/BombManPlayerCharacter.h"

void ABombManPowerup::OnPlayerCollision(ABombManPlayerCharacter* Character)
{
	if (!bPowerupActive)
	{
		PowerupStart(Character);
	}
}

void ABombManPowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABombManPowerup::PowerupStart(ABombManPlayerCharacter* Character)
{
	bPowerupActive = true;
	PowerupCharacter = Character;

	SetActorHiddenInGame(true);
}

void ABombManPowerup::PowerupEnd(ABombManPlayerCharacter* Character)
{
	Destroy();
}

void ABombManPowerup::PowerupEnd()
{
	PowerupEnd(PowerupCharacter);
}