// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniGameBananza/UI/Generic/MiniGamePlayersUI.h"
#include "MiniGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMiniGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UMiniGamePlayersUI> MiniGamePlayersClass;

private:
	UMiniGamePlayersUI* GamePlayersUI;
	
};
