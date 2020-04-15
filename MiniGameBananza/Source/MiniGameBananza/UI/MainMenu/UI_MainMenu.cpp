// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void UUI_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton) 
	{
		StartGameButton->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickStartButton);
	}

	if (GameModeSelectionButton) {
		GameModeSelectionButton->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickGameModeSelectionButton);
	}
}

void UUI_MainMenu::OnClickStartButton() 
{
	const UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(TEXT("Bomberman_New")));
	}
}

void UUI_MainMenu::OnClickGameModeSelectionButton()
{
	const UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(TEXT("GameMode_Selection_Menu")));
	}

}