// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayerController.h"
#include "MiniGameBananza//UI/HUD/MiniGameHUD.h"

void AMiniGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	AMiniGameHUD* MiniGameHUD = GetMiniGameHUD();
	if (MiniGameHUD)
	{
		MiniGamePlayerUI = MiniGameHUD->GetMiniGamePlayerUI(this);
	}
}

AMiniGameHUD* AMiniGamePlayerController::GetMiniGameHUD()
{
	return Cast<AMiniGameHUD>(GetHUD());
}