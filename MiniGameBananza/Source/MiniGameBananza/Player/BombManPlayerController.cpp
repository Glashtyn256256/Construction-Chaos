// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerController.h"
#include "MiniGameBananza/Gamemode/BombManGamemode.h"
#include "Kismet/GameplayStatics.h"

void ABombManPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ABombManPlayerController::Tick(float DeltaTime)
{
	if (bIsRespawning)
	{
		RespawnCountdownTimer -= DeltaTime * RespawnCountdownModifier;
		if (RespawnCountdownTimer <= 0)
		{
			Respawn();
		}
	}
}

void ABombManPlayerController::StartRespawnProcess()
{
	if (NumLives > 0)
	{
		RespawnCountdownTimer = MaxRespawnTime;
		bIsRespawning = true;
	}
}

void ABombManPlayerController::Respawn()
{
	const UWorld* world = GetWorld();
	if (world)
	{
		ABombManGamemode* gamemode = Cast<ABombManGamemode>(UGameplayStatics::GetGameMode(world));
		if (gamemode)
		{
			if (gamemode->RespawnPlayer(this))
			{
				--NumLives;
			}
		}
	}
	bIsRespawning = false;
}


