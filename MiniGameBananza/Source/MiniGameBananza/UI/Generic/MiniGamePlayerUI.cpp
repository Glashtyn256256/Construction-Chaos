// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayerUI.h"
#include "MiniGameBananza/UI/HUD/MiniGameHUD.h"
#include "MiniGameBananza/Player/MiniGamePlayerController.h"

void UMiniGamePlayerUI::InitializeUI(AMiniGamePlayerController* _Controller)
{
	if(!_Controller) return;

	Controller = _Controller;

	HUD = AMiniGameHUD::GetInstance();

	if (HeartClass && HeartsBox)
	{
		for (int i = 0; i < Controller->MaxLives; ++i)
		{
			UUserWidget* HeartWidget = CreateWidget< UUserWidget>(GetWorld(), HeartClass);
			if (HeartWidget)
			{
				Hearts.Add(HeartWidget);

				HeartsBox->AddChildToHorizontalBox(HeartWidget);
			}
		}
	}
}

void UMiniGamePlayerUI::SetLives(int lives)
{
	if (!Controller) return;

	int max = lives > Hearts.Num() ? Hearts.Num() : lives;

	int i = 0;
	for (; i < max; ++i)
	{
		Hearts[i]->SetVisibility(ESlateVisibility::Visible);
	}

	for (i; i < Hearts.Num();++i)
	{
		Hearts[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}