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

	if(ButtonMainMenu)
	{
		ButtonMainMenu->OnClicked.AddDynamic(this, &UWinScreenUI::OnMainMenu);
	}

	if (ButtonPlayAgain)
	{
		ButtonPlayAgain->OnClicked.AddDynamic(this, &UWinScreenUI::OnPlayAgain);
	}
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