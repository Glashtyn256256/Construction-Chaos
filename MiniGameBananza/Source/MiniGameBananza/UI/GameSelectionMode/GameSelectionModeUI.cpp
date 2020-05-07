// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSelectionModeUI.h"

void UGameSelectionModeUI::NativeConstruct()
{
	Super::NativeConstruct();

	SelectLevel.Add(GameModeLevels::Bomberman);
	SelectLevel.Add(GameModeLevels::FloorIsLava);
	SelectLevel.Add(GameModeLevels::GirderWipeout);

	MiniGameInstance = Cast<UMiniGameBananzaGameInstance>(GetGameInstance());

	if (MiniGameInstance)
	{
		MiniGameInstance->ResetScores();
		MiniGameInstance->SetIsGamemodeSelection(true);
		ArrayIndex = 0;

		if (MiniGameInstance->GetCurrentLevel())
		{
			ArrayIndex = SelectLevel.Find(MiniGameInstance->GetCurrentLevel());
			if(ArrayIndex < 0)
			{
				ArrayIndex = 0;
			}
		}
	}

	SetVisibilityOfAllImagesToHidden();

	InitializeComponents();

	DisplayMiniGameImageAndTitle(SelectLevel[ArrayIndex]);
};

	
void UGameSelectionModeUI::InitializeComponents()
{
	if(ButtonPlayMode)
	{
		ButtonPlayMode->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnPlayMode);
	}

	if (ButtonMainMenu)
	{
		ButtonMainMenu->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnMainMenu);
	}

	if(ButtonLeftArrow)
	{
		ButtonLeftArrow->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnLeftArrow);
	}

	if(ButtonRightArrow)
	{
		ButtonRightArrow->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnRightArrow);
	}
}

void UGameSelectionModeUI::OnLeftArrow()
{
	ArrayIndex--;
	if (ArrayIndex < 0)
	{
		ArrayIndex = SelectLevel.Num() - 1;
	}

	DisplayMiniGameImageAndTitle(SelectLevel[ArrayIndex]);
}

void UGameSelectionModeUI::OnRightArrow()
{
	ArrayIndex++;

	if (ArrayIndex > SelectLevel.Num() - 1)
	{
		ArrayIndex = 0;
	}

	DisplayMiniGameImageAndTitle(SelectLevel[ArrayIndex]);
}

void UGameSelectionModeUI::OnMainMenu()
{
	if (MiniGameInstance)
	{
		MiniGameInstance->SetGameMode(GameModeLevels::MainMenu);
	}
}

void UGameSelectionModeUI::OnPlayMode()
{
	if (MiniGameInstance)
	{
		MiniGameInstance->SetGameMode(SelectLevel[ArrayIndex]);
	}
}

void UGameSelectionModeUI::SetVisibilityOfAllImagesToHidden()
{
	if (!ImageBomberManGame || !ImageBomberManTitle || !ImageFloorIsLavaGame || !ImageFloorIsLavaTitle ||
		!ImageGirderWipeoutGame || !ImageGirderWipeoutTitle) return;
	ImageBomberManGame->SetVisibility(ESlateVisibility::Hidden);
	ImageBomberManTitle->SetVisibility(ESlateVisibility::Hidden);
	ImageFloorIsLavaGame->SetVisibility(ESlateVisibility::Hidden);
	ImageFloorIsLavaTitle->SetVisibility(ESlateVisibility::Hidden);
	ImageGirderWipeoutGame->SetVisibility(ESlateVisibility::Hidden);
	ImageGirderWipeoutTitle->SetVisibility(ESlateVisibility::Hidden);
}

void UGameSelectionModeUI::DisplayMiniGameImageAndTitle(GameModeLevels gamemode)
{
	SetVisibilityOfAllImagesToHidden();

	switch (gamemode)
	{
	case Bomberman:
		ImageBomberManGame->SetVisibility(ESlateVisibility::Visible);
		ImageBomberManTitle->SetVisibility(ESlateVisibility::Visible);
		break;
	case FloorIsLava:
		ImageFloorIsLavaGame->SetVisibility(ESlateVisibility::Visible);
		ImageFloorIsLavaTitle->SetVisibility(ESlateVisibility::Visible);
		break;
	case GirderWipeout:
		ImageGirderWipeoutGame->SetVisibility(ESlateVisibility::Visible);
		ImageGirderWipeoutTitle->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		ImageBomberManGame->SetVisibility(ESlateVisibility::Visible);
		ImageBomberManTitle->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}