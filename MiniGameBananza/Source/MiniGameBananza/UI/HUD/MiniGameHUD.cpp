// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameHUD.h"
#include "Engine/World.h"

AMiniGameHUD* AMiniGameHUD::HUDInstance = nullptr;

void AMiniGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MiniGamePlayersClass && GetWorld())
	{
		APlayerController* PlayerController = GetOwningPlayerController();
		if (PlayerController && PlayerController->GetLocalPlayer() && PlayerController->GetLocalPlayer()->GetControllerId() == 0)
		{
			HUDInstance = this;
			GamePlayersUI = CreateWidget<UMiniGamePlayersUI>(GetWorld(), MiniGamePlayersClass, FName(TEXT("MiniGamePlayers")));
		}
	}

	if (GamePlayersUI)
	{
		GamePlayersUI->AddToViewport();
	}
}

UMiniGamePlayerUI* AMiniGameHUD::GetMiniGamePlayerUI(APlayerController* Controller)
{
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