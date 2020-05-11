// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSelectionModeHUD.h"

void AGameSelectionModeHUD::BeginPlay()
{
	Super::BeginPlay();
	UWorld* world = GetWorld();
	if (world)
	{
		if (GetOwningPlayerController())
		{
			GetOwningPlayerController()->bShowMouseCursor = true;

			GameSelectionMode = CreateWidget<UGameSelectionModeUI>(GetOwningPlayerController(), GameSelectionModeClass, FName(TEXT("GameSelectionMode")));

			if (GameSelectionMode)
			{
				GameSelectionMode->AddToViewport(0);
			}
		}
	}
	
}