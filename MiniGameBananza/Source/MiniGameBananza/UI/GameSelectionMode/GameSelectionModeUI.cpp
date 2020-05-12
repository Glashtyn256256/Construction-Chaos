// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSelectionModeUI.h"

void UGameSelectionModeUI::NativeConstruct()
{
	Super::NativeConstruct();

	SelectLevel.Add(GameModeLevels::Bomberman);
	SelectLevel.Add(GameModeLevels::FloorIsLava);
	SelectLevel.Add(GameModeLevels::GirderWipeout);

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

	DisplayMiniGameImageAndTitle(SelectLevel[ArrayIndex]);
};

	
void UGameSelectionModeUI::InitializeComponents()
{
	if(ButtonPlayMode)
	{
		ButtonPlayMode->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnPlayMode);
		ButtonPlayMode->OnHovered.AddDynamic(this, &UGameSelectionModeUI::OnHoverButton);
	}

	if (ButtonMainMenu)
	{
		ButtonMainMenu->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnMainMenu);
		ButtonMainMenu->OnHovered.AddDynamic(this, &UGameSelectionModeUI::OnHoverButton);
	}

	if(ButtonLeftArrow)
	{
		ButtonLeftArrow->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnLeftArrow);
		ButtonLeftArrow->OnHovered.AddDynamic(this, &UGameSelectionModeUI::OnHoverButton);
	}

	if(ButtonRightArrow)
	{
		ButtonRightArrow->OnClicked.AddDynamic(this, &UGameSelectionModeUI::OnRightArrow);
		ButtonRightArrow->OnHovered.AddDynamic(this, &UGameSelectionModeUI::OnHoverButton);
	}
}

void UGameSelectionModeUI::OnLeftArrow()
{
	OnClickButton();

	ArrayIndex--;
	if (ArrayIndex < 0)
	{
		ArrayIndex = SelectLevel.Num() - 1;
	}

	DisplayMiniGameImageAndTitle(SelectLevel[ArrayIndex]);
}

void UGameSelectionModeUI::OnRightArrow()
{
	OnClickButton();

	ArrayIndex++;

	if (ArrayIndex > SelectLevel.Num() - 1)
	{
		ArrayIndex = 0;
	}

	DisplayMiniGameImageAndTitle(SelectLevel[ArrayIndex]);
}

void UGameSelectionModeUI::OnMainMenu()
{
	if (scClick_Low)
	{
		PlaySoundAndActionWhenFinished(scClick_Low, FOnAction::CreateLambda([this]()
			{
				if (MiniGameInstance)
				{
					MiniGameInstance->SetGameMode(GameModeLevels::MainMenu);
				}
			}));
	}
}

void UGameSelectionModeUI::OnPlayMode()
{
	if (scStart)
	{
		PlaySoundAndActionWhenFinished(scStart, FOnAction::CreateLambda([this]()
			{
				if (MiniGameInstance)
				{
					MiniGameInstance->SetGameMode(SelectLevel[ArrayIndex]);
				}
			}));
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