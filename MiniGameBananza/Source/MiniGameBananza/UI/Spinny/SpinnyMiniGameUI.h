// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "SpinnyMiniGameUI.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API USpinnyMiniGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* SpeedLevel;

public:
	void SetSpeedLevel(int speedLevel);
	
};
