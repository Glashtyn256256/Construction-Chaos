// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerController.h"
#include "BombManPlayerCharacter.h"
#include "MiniGameBananza/Gamemode/BombManGamemode.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

ABombManPlayerController::ABombManPlayerController()
	: bIsRespawning(false), TimeUntilRespawn(MaxRespawnTime)
{

}

void ABombManPlayerController::BeginPlay()
{
	
}

void ABombManPlayerController::Tick(float DeltaTime)
{
	if (bIsRespawning)
	{
		TimeUntilRespawn -= DeltaTime * RespawnModifier;
		if (TimeUntilRespawn <= 0)
		{
			Respawn();
		}
	}
}

void ABombManPlayerController::OnHit(AActor* ActorToDestroy, ABombManPlayerController* DamageCauser)
{
	if (ActorToDestroy)
	{
		ActorToDestroy->Destroy();
		NumLives--;

		if (NumLives > 0)
		{
			StartRespawning();
		}
	}
}

void ABombManPlayerController::StartRespawning()
{
	TimeUntilRespawn = MaxRespawnTime;
	bIsRespawning = true;
}

void ABombManPlayerController::Respawn()
{
	const UWorld* world = GetWorld();
	if (world)
	{
		ABombManGamemode* gamemode = Cast<ABombManGamemode>(UGameplayStatics::GetGameMode(world));
		if (gamemode)
		{
			gamemode->RespawnPlayer(this);
		}
	}
	bIsRespawning = false;
}