// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayerController.h"
#include "MiniGameBananza//UI/HUD/MiniGameHUD.h"
#include "MiniGameBananza/Gamemode/MiniGameBananzaGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AMiniGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	AMiniGameHUD* MiniGameHUD = GetMiniGameHUD();
	if (MiniGameHUD)
	{
		MiniGamePlayerUI = MiniGameHUD->GetMiniGamePlayerUI(this);
	}

	if (MiniGamePlayerUI)
	{
		MiniGamePlayerUI->InitializeUI(this);

		MiniGamePlayerUI->SetLives(NumLives);
	}
}

AMiniGameHUD* AMiniGamePlayerController::GetMiniGameHUD()
{
	return Cast<AMiniGameHUD>(GetHUD());
}

void AMiniGamePlayerController::Tick(float DeltaTime)
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

void AMiniGamePlayerController::StartRespawnProcess()
{
	if (NumLives > 0)
	{
		RespawnCountdownTimer = MaxRespawnTime;
		bIsRespawning = true;
	}
}

void AMiniGamePlayerController::Respawn()
{
	const UWorld* world = GetWorld();
	if (world)
	{
		AMiniGameBananzaGameModeBase* gamemode = Cast<AMiniGameBananzaGameModeBase>(UGameplayStatics::GetGameMode(world));
		if (gamemode)
		{
			gamemode->RestartPlayer(this);

			SetLives(--NumLives);
		}
	}
	bIsRespawning = false;
}

void AMiniGamePlayerController::SetLives(int lives)
{
	this->NumLives = lives;
	if (this->NumLives > MaxLives)
	{
		this->NumLives = MaxLives;
	}
	else if (this->NumLives < 0)
	{
		this->NumLives = 0;
	}

	if (MiniGamePlayerUI)
	{
		MiniGamePlayerUI->SetLives(NumLives);
	}

}
int AMiniGamePlayerController::GetLives() const
{
	return NumLives;
}