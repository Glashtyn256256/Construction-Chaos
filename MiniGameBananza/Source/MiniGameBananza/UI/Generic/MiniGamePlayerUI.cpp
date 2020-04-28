// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayerUI.h"
#include "MiniGameBananza/UI/HUD/MiniGameHUD.h"
#include "MiniGameBananza/Player/MiniGamePlayerController.h"

void UMiniGamePlayerUI::InitializeUI(AMiniGamePlayerController* _Controller)
{
	if (!_Controller) return;

	Controller = _Controller;

	HUD = AMiniGameHUD::GetInstance();

	Hearts.Empty();
	Hearts.Add(PlayerHeart1);
	Hearts.Add(PlayerHeart2);
	Hearts.Add(PlayerHeart3);

	SetLivesUI(Controller->MaxLives);
}

void UMiniGamePlayerUI::SetLivesUI(int lives)
{
	if (!Controller) return;

	int max = lives > Hearts.Num() ? Hearts.Num() : lives;

	int i = 0;
	for (; i < max; ++i)
	{
		Hearts[i]->SetVisibility(ESlateVisibility::Visible);
	}

	for (i; i < Hearts.Num(); ++i)
	{
		Hearts[i]->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMiniGamePlayerUI::SetScoreUI(int score)
{
	if (!Controller) return;

	PlayerScore->SetText(FText::FromString(FString::FromInt(score)));
}