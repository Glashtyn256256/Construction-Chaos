// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Classes/Sound/SoundCue.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"
#include "MiniGameBananzaMenuUI_Base.generated.h"

DECLARE_DELEGATE(FOnAction);

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UMiniGameBananzaMenuUI_Base : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	// Used for when the button changes the map and terminates the sound early - waits until sound is finished then performs action
	// otherwise just use PlaySound() as the sound should persist if on the same map
	virtual void PlaySoundAndActionWhenFinished(USoundBase* SoundBase, FOnAction action);
	virtual void InitializeComponents();

	UFUNCTION()
	void OnHoverButton();
	UFUNCTION()
	void OnClickButton();
	UFUNCTION()
	void OnClickBackButton();

private:
	void HandleAction(float DeltaTime);

	void HandleMusicLoop(float DeltaTime);

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

	UPROPERTY(EditDefaultsOnly)
	UMiniGameBananzaGameInstance* MiniGameInstance;

private:
	FOnAction OnUIAction;
	float ActionTimer = 0.0f;

	float MusicLoopTimer = 0.0f;

};
