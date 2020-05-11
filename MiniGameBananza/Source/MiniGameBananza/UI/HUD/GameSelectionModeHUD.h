// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniGameBananza/UI/GameSelectionMode/GameSelectionModeUI.h"
#include "GameSelectionModeHUD.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AGameSelectionModeHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UGameSelectionModeUI> GameSelectionModeClass;

private:
	UGameSelectionModeUI* GameSelectionMode;
};
