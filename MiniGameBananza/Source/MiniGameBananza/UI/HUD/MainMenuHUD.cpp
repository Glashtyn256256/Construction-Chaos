// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuHUD.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world)
	{
		if (GetOwningPlayerController())
		{
			GetOwningPlayerController()->bShowMouseCursor = true;

			MainMenu = CreateWidget<UUI_MainMenu>(GetOwningPlayerController(), MainMenuClass, FName(TEXT("GameSelectionMode")));

			if (MainMenu)
			{
				MainMenu->AddToViewport(0);
			}
		}
	}
}