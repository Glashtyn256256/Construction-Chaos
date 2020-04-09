// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPowerupHealth.h"
#include "MiniGameBananza/Player/BombManPlayerCharacter.h"
#include "MiniGameBananza/Player/BombManPlayerController.h"

void ABombManPowerupHealth::PowerupStart(ABombManPlayerCharacter* Character)
{
	Super::PowerupStart(Character);

	ABombManPlayerController* Controller = Cast< ABombManPlayerController>(Character->GetController());
	if (Controller)
	{
		Controller->SetLives(Controller->GetLives() + Lives);
	}

	Super::PowerupEnd();
}

void ABombManPowerupHealth::PowerupEnd(ABombManPlayerCharacter * Character)
{
	Super::PowerupEnd(Character);
}
