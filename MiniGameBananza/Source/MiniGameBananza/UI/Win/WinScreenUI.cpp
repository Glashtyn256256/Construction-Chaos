// Fill out your copyright notice in the Description page of Project Settings.


#include "WinScreenUI.h"

void UWinScreenUI::NativeConstruct()
{
	Super::NativeConstruct();

	MiniGameInstance = Cast<UMiniGameBananzaGameInstance>(GetGameInstance());
	if (MiniGameInstance)
	{
		MiniGameInstance->SetIsGamemodeSelection(false);
	}

	InitializeUIComponents();
}

	

void UWinScreenUI::OnMainMenu()
{
	UWorld* World = this->GetWorld();
	if (World && MiniGameInstance)
	{
		MiniGameInstance->SetGameMode(GameModeLevels::MainMenu);
	}
}

void UWinScreenUI::OnPlayAgain()
{
	UWorld* World = this->GetWorld();
	if (World && MiniGameInstance)
	{
		MiniGameInstance->ResetScores();
		MiniGameInstance->SetGameMode(GameModeLevels::Bomberman);
	}
}

void UWinScreenUI::InitializeUIComponents() 
{
	if (ButtonMainMenu)
	{
		ButtonMainMenu->OnClicked.AddDynamic(this, &UWinScreenUI::OnMainMenu);
	}

	if (ButtonPlayAgain)
	{
		ButtonPlayAgain->OnClicked.AddDynamic(this, &UWinScreenUI::OnPlayAgain);
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