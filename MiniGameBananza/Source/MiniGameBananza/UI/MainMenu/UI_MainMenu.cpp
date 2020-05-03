// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void UUI_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	MiniGameInstance = Cast<UMiniGameBananzaGameInstance>(GetGameInstance());
	if (MiniGameInstance)
	{
		MiniGameInstance->ResetScores();
		MiniGameInstance->SetIsGamemodeSelection(false);
	}

	InitializeComponents();
}

void UUI_MainMenu::InitializeComponents()
{
	if (ButtonStart)
	{
		ButtonStart->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickStartButton);
		ButtonStart->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonGameModes)
	{
		ButtonGameModes->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickGameModeSelectionButton);
		ButtonGameModes->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonInstructions)
	{
		//ButtonStart->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickStartButton);
		ButtonInstructions->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonSettings)
	{
		//ButtonGameModes->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickGameModeSelectionButton);
		ButtonSettings->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonExit)
	{
		//ButtonGameModes->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickGameModeSelectionButton);
		ButtonExit->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}
}

void UUI_MainMenu::OnClickStartButton()
{
	MiniGameInstance->SetGameMode(GameModeLevels::Bomberman);
}

void UUI_MainMenu::OnClickGameModeSelectionButton()
{
	const UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(TEXT("GameMode_Selection_Menu")));
	}

}

void UUI_MainMenu::OnHoverButton()
{
	if (scHover)
	{
		PlaySound(scHover);
	}
}
