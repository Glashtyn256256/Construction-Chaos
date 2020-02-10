// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManGamemode.h"
#include "MiniGameBananza/Player/BombManPlayerCharacter.h"
#include "Core/Public/Misc/AssertionMacros.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

void ABombManGamemode::BeginPlay()
{
	class UWorld* const world = GetWorld();
	if (world)
	{
		for (int i = 0; i <= PlayerCount; ++i)
		{
			UGameplayStatics::CreatePlayer(world, i);
		}
	}
}