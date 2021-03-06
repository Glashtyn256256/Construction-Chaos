// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MiniGameBananza/UI/Generic/MiniGamePlayersUI.h"
#include "MiniGameBananza/UI/Generic/MiniGamePlayerUI.h"
#include "MiniGameBananza/UI/Generic/MiniGameReadyCountdown.h"
#include "MiniGameHUD.generated.h"

class AMiniGamePlayerController;

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMiniGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void CreateInstance();
	virtual void CreateUI();
	virtual void BeginDestroy() override;

	UMiniGamePlayerUI* GetMiniGamePlayerUI(AMiniGamePlayerController* Controller);
	UMiniGameReadyCountdown* GetMiniGameCountdown() const;

	static AMiniGameHUD* GetInstance();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UMiniGamePlayersUI> MiniGamePlayersClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UMiniGameReadyCountdown> MiniGameReadyCountdownClass;

private:
	UMiniGamePlayersUI* GamePlayersUI;
	UMiniGameReadyCountdown* ReadyCountdown;
};
