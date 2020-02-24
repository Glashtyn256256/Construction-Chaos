// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Containers/Array.h"
#include "Components/HorizontalBox.h"
#include "MiniGamePlayerUI.generated.h"

class AMiniGamePlayerController;

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UMiniGamePlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void InitializeUI(AMiniGamePlayerController* Controller);
	virtual void SetLives(int lives);


public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HeartClass;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UHorizontalBox* HeartsBox;

protected:
	UPROPERTY()
	AMiniGamePlayerController* Controller;

	UPROPERTY()
	TArray<UUserWidget*> Hearts;

	class AMiniGameHUD* HUD;
};
