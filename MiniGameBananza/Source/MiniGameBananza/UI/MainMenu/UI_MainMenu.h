// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"
#include "Components/Button.h"
#include "Components/AudioComponent.h"
#include "Engine/Classes/Sound/SoundCue.h"
#include "Layout/Geometry.h"
#include "UI_MainMenu.generated.h"

DECLARE_DELEGATE(FOnAction);

UCLASS()
class MINIGAMEBANANZA_API UUI_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void InitializeComponents();

	// Used for when the button changes the map and terminates the sound early - waits until sound is finished then performs action
	// otherwise just use PlaySound() as the sound should persist if on the same map
	void PlaySoundAndActionWhenFinished(USoundBase* SoundBase, FOnAction action);
	void HandleAction(float DeltaTime);

	void HandleMusicLoop(float DeltaTime);

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
	UFUNCTION()
	void OnHoverButton();
	UFUNCTION()
	void OnClickButton();
	UFUNCTION()
	void OnClickBackButton();

#pragma endregion
public:
#pragma region Sound Cues

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* scMusic;

	// used when hovering a button
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* scHover;

	// used for buttons that open new dialog / pages
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* scClick_High;
	
	// used for back buttons etc
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* scClick_Low;

	// used for starting the game
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* scStart;

	// used when exitting the game
	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* scExit;

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

private:
	FOnAction OnUIAction;
	float ActionTimer = 0.0f;

	float MusicLoopTimer = 0.0f;
};
