// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGameBananza/UI/Generic/MiniGameBananzaMenuUI_Base.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "GameSelectionModeUI.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UGameSelectionModeUI : public UMiniGameBananzaMenuUI_Base
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	virtual void InitializeComponents();

	virtual void DisplayMiniGameImageAndTitle(GameModeLevels gamemode);

	void SetVisibilityOfAllImagesToHidden();

#pragma region Events

	UFUNCTION()
	void OnRightArrow();
	UFUNCTION()
	void OnLeftArrow();
	UFUNCTION()
	void OnPlayMode();
	UFUNCTION()
	void OnMainMenu();

#pragma endregion

protected:
	//UMiniGameBananzaGameInstance* MiniGameInstance;

	TArray<GameModeLevels> SelectLevel;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageBomberManGame;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageBomberManTitle;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageFloorIsLavaGame;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageFloorIsLavaTitle;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageGirderWipeoutGame;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageGirderWipeoutTitle;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonPlayMode;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonMainMenu;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonLeftArrow;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonRightArrow;

	int ArrayIndex;
};
