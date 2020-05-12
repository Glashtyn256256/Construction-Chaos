// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

void UUI_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (MiniGameInstance)
	{
		MiniGameInstance->ResetScores();
	}
}

void UUI_MainMenu::InitializeComponents()
{
	if (ButtonStart)
	{
		ButtonStart->OnClicked.AddDynamic(this, &UUI_MainMenu::OnStart);
		ButtonStart->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonGameModes)
	{
		ButtonGameModes->OnClicked.AddDynamic(this, &UUI_MainMenu::OnGameModeSelection);
		ButtonGameModes->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonInstructions)
	{
		ButtonInstructions->OnClicked.AddDynamic(this, &UUI_MainMenu::OnInstructions);
		ButtonInstructions->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonSettings)
	{
		ButtonSettings->OnClicked.AddDynamic(this, &UUI_MainMenu::OnSettings);
		ButtonSettings->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonExit)
	{
		ButtonExit->OnClicked.AddDynamic(this, &UUI_MainMenu::OnExit);
		ButtonExit->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}
}

void UUI_MainMenu::OnStart()
{
	if (scStart)
	{
		PlaySoundAndActionWhenFinished(scStart, FOnAction::CreateLambda([this]()
			{
				MiniGameInstance->SetGameMode(GameModeLevels::Bomberman);
			}));
	}
}

void UUI_MainMenu::OnGameModeSelection()
{
	if (scClick_High)
	{
		PlaySoundAndActionWhenFinished(scClick_High, FOnAction::CreateLambda([this]()
			{
				const UWorld* World = GetWorld();
				if (World)
				{
					MiniGameInstance->SetCurrentLevel(GameModeLevels::Bomberman);
					UGameplayStatics::OpenLevel(World, FName(TEXT("GameMode_Selection_Menu")));
				}
			}));
	}
}

void UUI_MainMenu::OnInstructions()
{
	OnClickButton();
}

void UUI_MainMenu::OnSettings()
{
	OnClickButton();
}

void UUI_MainMenu::OnExit()
{
	if (scExit)
	{
		PlaySoundAndActionWhenFinished(scExit, FOnAction::CreateLambda([this]()
			{
				TEnumAsByte<EQuitPreference::Type> pref = TEnumAsByte<EQuitPreference::Type>(EQuitPreference::Quit);
				UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, pref, false);
			}));
	}
}
