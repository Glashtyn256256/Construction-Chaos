// Fill out your copyright notice in the Description page of Project Settings.


#include "WinScreenHUD.h"

void AWinScreenHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (world)
	{
		if (GetOwningPlayerController())
		{
			GetOwningPlayerController()->bShowMouseCursor = true;

			WinScreen = CreateWidget<UWinScreenUI>(GetOwningPlayerController(), WinScreenClass, FName(TEXT("GameSelectionMode")));

			if (WinScreen)
			{
				WinScreen->AddToViewport(0);
			}
		}
	}
}