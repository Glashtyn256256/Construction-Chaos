// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "MiniGameBananza/UI/Generic/MiniGameBananzaUI_Base.h"
#include "Components/Button.h"
#include "Components/AudioComponent.h"
#include "Engine/Classes/Sound/SoundCue.h"
#include "Layout/Geometry.h"
#include "UI_MainMenu.generated.h"


UCLASS()
class MINIGAMEBANANZA_API UUI_MainMenu : public UMiniGameBananzaUI_Base
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	virtual void InitializeComponents() override;


#pragma region Events

	UFUNCTION()
	void OnStart();
	UFUNCTION()
	void OnGameModeSelection();
	UFUNCTION()
	void OnInstructions();
	UFUNCTION()
	void OnSettings();
	UFUNCTION()
	void OnExit();

#pragma endregion
public:
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


};
