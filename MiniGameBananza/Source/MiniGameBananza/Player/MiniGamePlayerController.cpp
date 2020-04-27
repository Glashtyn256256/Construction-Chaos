// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayerController.h"
#include "MiniGameBananza/Gamemode/MiniGameBananzaGameModeBase.h"
#include "MiniGameBananza//UI/HUD/MiniGameHUD.h"
#include "Kismet/GameplayStatics.h"

void AMiniGamePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

AMiniGameHUD* AMiniGamePlayerController::GetMiniGameHUD()
{
	return GetHUD<AMiniGameHUD>();
}

void AMiniGamePlayerController::Tick(float DeltaTime)
{
	CheckHUD();

	if (bIsRespawning)
	{
		RespawnCountdownTimer -= DeltaTime * RespawnCountdownModifier;
		if (RespawnCountdownTimer <= 0)
		{
			Respawn();
		}
	}
}

void AMiniGamePlayerController::CheckHUD()
{
	if (!MiniGamePlayerUI)
	{
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
}

void AMiniGamePlayerController::StartRespawnProcess()
{
	if (NumLives > 0)
	{
		SetNumLives(--NumLives);
		RespawnCountdownTimer = MaxRespawnTime;
		bIsRespawning = true;
	}
}

void AMiniGamePlayerController::Respawn()
{
	const UWorld* world = GetWorld();
	if (world)
	{
		if (!HasRanOutOfLives())
		{
			AMiniGameBananzaGameModeBase* gamemode = Cast<AMiniGameBananzaGameModeBase>(UGameplayStatics::GetGameMode(world));
			if (gamemode)
			{
				gamemode->RestartPlayer(this);

			}
		}
		else
		{
			OnDead();
		}
	}
	bIsRespawning = false;
}

void AMiniGamePlayerController::OnDead()
{
	TArray<AMiniGamePlayerController*> DeadControllers;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AMiniGamePlayerController* PlayerController = Cast<AMiniGamePlayerController>(Iterator->Get());
		if (PlayerController && PlayerController->HasRanOutOfLives() && PlayerController != this)
		{
			DeadControllers.Add(PlayerController);
		}
	}

	int DeadCount = DeadControllers.Num();

	UpdateScore(DeadCount);
}

void AMiniGamePlayerController::SetNumLives(int lives)
{
	NumLives = lives;
	if (NumLives > MaxLives)
	{
		NumLives = MaxLives;
	}
	else if (NumLives < 0)
	{
		NumLives = 0;
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

bool AMiniGamePlayerController::HasRanOutOfLives() const
{
	return NumLives <= 0;
}

void AMiniGamePlayerController::UpdateScore(int score) const
{
	UMiniGameBananzaGameInstance* MiniGameInstance = Cast< UMiniGameBananzaGameInstance>(GetGameInstance());
	if (MiniGameInstance)
	{
		ULocalPlayer* LocalPlayer = GetLocalPlayer();
		if (LocalPlayer)
		{
			int PlayerID = LocalPlayer->GetControllerId();

			MiniGameInstance->UpdateScore(PlayerID, score);
		}
	}
}
int AMiniGamePlayerController::GetScore() const
{
	int Score = 0;

	UMiniGameBananzaGameInstance* MiniGameInstance = Cast< UMiniGameBananzaGameInstance>(GetGameInstance());
	if (MiniGameInstance)
	{
		ULocalPlayer* LocalPlayer = GetLocalPlayer();
		if (LocalPlayer)
		{
			int PlayerID = LocalPlayer->GetControllerId();

			Score = MiniGameInstance->GetScore(PlayerID);
		}
	}

	return Score;
}