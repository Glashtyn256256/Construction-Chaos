// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPowerup.h"
#include "MiniGameBananza/Player/BombManPlayerCharacter.h"

void ABombManPowerup::OnPlayerCollision(ABombManPlayerCharacter* Character)
{
	if (!bPowerupActive)
	{
		OnPowerupStart(Character);
	}
}

void ABombManPowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABombManPowerup::OnPowerupStart(ABombManPlayerCharacter* Character)
{
	bPowerupActive = true;
	PowerupCharacter = Character;

	SetActorHiddenInGame(true);
}

void ABombManPowerup::OnPowerupEnd(ABombManPlayerCharacter* Character)
{
	Destroy();
}

void ABombManPowerup::OnPowerupEnd()
{
	OnPowerupEnd(PowerupCharacter);
}