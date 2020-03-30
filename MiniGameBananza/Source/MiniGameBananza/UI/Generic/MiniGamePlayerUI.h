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
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* PlayerHeart1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* PlayerHeart2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* PlayerHeart3;

protected:
	UPROPERTY()
	AMiniGamePlayerController* Controller;

	UPROPERTY()
	TArray<UUserWidget*> Hearts;

	class AMiniGameHUD* HUD;
};
