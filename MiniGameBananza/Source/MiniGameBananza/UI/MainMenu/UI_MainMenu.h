// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"
#include "Components/Button.h"
#include "Components/AudioComponent.h"
#include "Engine/Classes/Sound/SoundCue.h"
#include "UI_MainMenu.generated.h"


UCLASS()
class MINIGAMEBANANZA_API UUI_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void InitializeComponents();

#pragma region Events

	UFUNCTION()
	void OnClickStartButton();
	UFUNCTION()
	void OnClickGameModeSelectionButton();
	UFUNCTION()
	void OnHoverButton();

#pragma endregion
public:
#pragma region Sound Cues

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* scHover;

#pragma endregion

	UPROPERTY(EditAnywhere,meta = (BindWidget))
	UButton* ButtonStart;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonGameModes;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonInstructions;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonSettings;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonExit;

	UPROPERTY(EditDefaultsOnly)
	UMiniGameBananzaGameInstance* MiniGameInstance;
};
