// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "UI_MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UUI_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(EditDefaultsOnly,meta = (BindWidget))
	UButton* StartGameButton;



};
