// Fill out your copyright notice in the Description page of Project Settings.


#include "WinScreenUI.h"

void UWinScreenUI::OnMainMenu()
{
	if (scClick_Low)
	{
		PlaySoundAndActionWhenFinished(scClick_Low, FOnAction::CreateLambda([this]()
			{
				MiniGameInstance->SetGameMode(GameModeLevels::MainMenu);
			}));
	}
}

void UWinScreenUI::OnPlayAgain()
{
	if (scStart)
	{
		PlaySoundAndActionWhenFinished(scStart, FOnAction::CreateLambda([this]()
			{
				MiniGameInstance->ResetScores();
				MiniGameInstance->SetGameMode(GameModeLevels::Bomberman);
			}));
	}
}

void UWinScreenUI::InitializeComponents()
{
	if (ButtonMainMenu)
	{
		ButtonMainMenu->OnClicked.AddDynamic(this, &UWinScreenUI::OnMainMenu);
		ButtonMainMenu->OnHovered.AddDynamic(this, &UWinScreenUI::OnHoverButton);
	}

	if (ButtonPlayAgain)
	{
		ButtonPlayAgain->OnClicked.AddDynamic(this, &UWinScreenUI::OnPlayAgain);
		ButtonPlayAgain->OnHovered.AddDynamic(this, &UWinScreenUI::OnHoverButton);
	}

	if (TextPlayer1)
	{
		TextPlayer1->SetText(FText::FromString(FString::FromInt(MiniGameInstance->GetScore(0))));
	}

	if (TextPlayer2)
	{
		TextPlayer2->SetText(FText::FromString(FString::FromInt(MiniGameInstance->GetScore(1))));
	}

	if (TextPlayer3)
	{
		TextPlayer3->SetText(FText::FromString(FString::FromInt(MiniGameInstance->GetScore(2))));
	}

	if (TextPlayer4)
	{
		TextPlayer4->SetText(FText::FromString(FString::FromInt(MiniGameInstance->GetScore(3))));
	}
}