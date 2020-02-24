// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MiniGamePlayerUI.h"
#include "GameFramework/PlayerController.h"
#include "MiniGamePlayersUI.generated.h"

class AMiniGamePlayerController;

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UMiniGamePlayersUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UMiniGamePlayerUI* GetMiniGamePlayerUI(AMiniGamePlayerController* Controller);

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMiniGamePlayerUI* PlayerUI_0;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMiniGamePlayerUI* PlayerUI_1;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMiniGamePlayerUI* PlayerUI_2;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UMiniGamePlayerUI* PlayerUI_3;
};
