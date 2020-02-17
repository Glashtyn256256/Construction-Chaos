// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"
#include "Components/Button.h"
#include "UI_MainMenu.generated.h"


UCLASS()
class MINIGAMEBANANZA_API UUI_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnClickStartButton();
	void OnClickGameModeSelectionButton();
public:
	//TSubclassOf<class UUserWidget> 

	UPROPERTY(EditAnywhere,meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* GameModeSelectionButton;
};
