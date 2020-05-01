// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/UI/Spinny/SpinnyMiniGameUI.h"
#include "MiniGameBananza/UI/HUD/MiniGameHUD.h"
#include "SpinnyMiniGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ASpinnyMiniGameHUD : public AMiniGameHUD
{
	GENERATED_BODY()

public:
	virtual void CreateUI() override;

	void SetSpeedLevel(int speedLevel);

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USpinnyMiniGameUI> SpinnyMiniGameUIClass;

private:
	USpinnyMiniGameUI* SpinnyMiniGameUI;
	
};
