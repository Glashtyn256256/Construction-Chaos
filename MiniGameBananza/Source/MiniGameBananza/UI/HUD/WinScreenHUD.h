// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniGameBananza/UI/Win/WinScreenUI.h"
#include "WinScreenHUD.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AWinScreenHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UWinScreenUI> WinScreenClass;

private:
	UWinScreenUI* WinScreen;
};
