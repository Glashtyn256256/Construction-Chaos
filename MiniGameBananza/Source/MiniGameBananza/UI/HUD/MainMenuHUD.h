// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniGameBananza/UI//MainMenu/UI_MainMenu.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
		TSubclassOf<UUI_MainMenu> MainMenuClass;

private:
	UUI_MainMenu* MainMenu;
};
