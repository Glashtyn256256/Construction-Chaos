// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameHUD.h"
#include "Engine/World.h"

void AMiniGameHUD::BeginPlay()
{
	if (MiniGamePlayersClass && GetWorld())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			GamePlayersUI = CreateWidget<UMiniGamePlayersUI>(PlayerController, MiniGamePlayersClass, FName(TEXT("MiniGamePlayers")));
		}
	}

	if (GamePlayersUI)
	{
		GamePlayersUI->AddToViewport();
	}
}