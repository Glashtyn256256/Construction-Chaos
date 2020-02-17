// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniGameBananza/UI/Generic/MiniGamePlayersUI.h"
#include "MiniGameBananza/UI/Generic/MiniGamePlayerUI.h"
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

	UMiniGamePlayerUI* GetMiniGamePlayerUI(APlayerController* Controller);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UMiniGamePlayersUI> MiniGamePlayersClass;

private:
	UMiniGamePlayersUI* GamePlayersUI;
	
	static AMiniGameHUD* HUDInstance;
};
