// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"
#include "MiniGameBananza/UI/Generic/MiniGameBananzaUI_Base.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/UserWidget.h"
#include "WinScreenUI.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UWinScreenUI : public UMiniGameBananzaUI_Base
{
	GENERATED_BODY()
public:

	virtual void InitializeComponents() override;

#pragma region Events

	UFUNCTION()
	void OnPlayAgain();
	UFUNCTION()
	void OnMainMenu();

#pragma endregion
	
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonPlayAgain;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonMainMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextPlayer1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextPlayer2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextPlayer3;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TextPlayer4;
};
