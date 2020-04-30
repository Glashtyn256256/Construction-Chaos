// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MiniGameReadyCountdown.generated.h"

enum class ECountdownState
{
	None,
	Ready,
	Three,
	Two,
	One,
	Go
};
/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UMiniGameReadyCountdown : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;

	void SetCountdownState(ECountdownState state);
	bool NextCountdownState(ECountdownState& state);

protected:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* uReadyWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* uGoWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* uThreeWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* uTwoWidget;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* uOneWidget;
};
