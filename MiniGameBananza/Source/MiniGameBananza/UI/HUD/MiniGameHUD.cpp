// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameHUD.h"
#include "Engine/World.h"
#include "MiniGameBananza/Player/MiniGamePlayerController.h"
#include "GameFramework/PlayerController.h"

static AMiniGameHUD* HUDInstance = nullptr;

void AMiniGameHUD::BeginPlay()
{
	Super::BeginPlay();

	CreateInstance();
}

void AMiniGameHUD::BeginDestroy()
{
	Super::BeginDestroy();

	if (HUDInstance == this)
		HUDInstance = nullptr;
}

void AMiniGameHUD::CreateInstance()
{
	if (HUDInstance) return;

	if (MiniGamePlayersClass && GetWorld())
	{
		APlayerController* PlayerController = GetOwningPlayerController();
		if (PlayerController && !HUDInstance)
		{
			HUDInstance = this;
		}
	}

	if (HUDInstance)
	{
		CreateUI();
	}

}

void AMiniGameHUD::CreateUI()
{
	GamePlayersUI = CreateWidget<UMiniGamePlayersUI>(GetWorld(), MiniGamePlayersClass, FName(TEXT("MiniGamePlayers")));

	if (GamePlayersUI)
	{
		GamePlayersUI->AddToViewport(0);
	}

	ReadyCountdown = CreateWidget<UMiniGameReadyCountdown>(GetWorld(), MiniGameReadyCountdownClass, FName(TEXT("MiniGameReadyCountdown")));

	if (ReadyCountdown)
	{
		ReadyCountdown->AddToViewport(1);
	}
}

UMiniGamePlayerUI* AMiniGameHUD::GetMiniGamePlayerUI(AMiniGamePlayerController* Controller)
{
	CreateInstance();

	if (HUDInstance && HUDInstance != this)
	{
		return HUDInstance->GetMiniGamePlayerUI(Controller);
	}
	else
	{
		if (GamePlayersUI)
		{
			return GamePlayersUI->GetMiniGamePlayerUI(Controller);
		}
	}

	return nullptr;
}

UMiniGameReadyCountdown* AMiniGameHUD::GetMiniGameCountdown() const
{
	return ReadyCountdown;
}

AMiniGameHUD * AMiniGameHUD::GetInstance()
{
	return HUDInstance;
}
