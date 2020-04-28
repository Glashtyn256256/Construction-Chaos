// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Containers/Array.h"
#include "Components/HorizontalBox.h"
#include "MiniGamePlayerUI.generated.h"

class AMiniGamePlayerController;

UCLASS()
class MINIGAMEBANANZA_API UMiniGamePlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void InitializeUI(AMiniGamePlayerController* Controller);
	virtual void SetLivesUI(int lives);
	virtual void SetScoreUI(int score);


public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* PlayerHeart1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* PlayerHeart2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UUserWidget* PlayerHeart3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	//UEditableTextBox* ScorePlayer;
	UTextBlock* PlayerScore;
		
protected:
	UPROPERTY()
	AMiniGamePlayerController* Controller;

	UPROPERTY()
	TArray<UUserWidget*> Hearts;

	class AMiniGameHUD* HUD;
};
