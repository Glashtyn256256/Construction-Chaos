// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyMiniGameHUD.h"

void ASpinnyMiniGameHUD::CreateUI()
{
	Super::CreateUI();

	SpinnyMiniGameUI = CreateWidget<USpinnyMiniGameUI>(GetWorld(), SpinnyMiniGameUIClass, FName(TEXT("SpinnyUI")));

	if (SpinnyMiniGameUI)
	{
		SpinnyMiniGameUI->SetSpeedLevel(1);
		SpinnyMiniGameUI->AddToViewport(0);
	}
}

void ASpinnyMiniGameHUD::SetSpeedLevel(int speedLevel)
{
	if (SpinnyMiniGameUI)
	{
		SpinnyMiniGameUI->SetSpeedLevel(speedLevel);
	}
}
