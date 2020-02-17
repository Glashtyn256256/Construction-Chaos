// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "UI_MainMenu.h"

void UUI_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton) 
	{
		StartGameButton->OnClicked.AddDynamic(this, &UUI_MainMenu::OnClickStartButton);
	}
}

void UUI_MainMenu::OnClickStartButton() 
{
	const UWorld* World = GetWorld();

	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName(TEXT("Test")));
	}
}