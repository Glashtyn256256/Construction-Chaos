// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameReadyCountdown.h"

void UMiniGameReadyCountdown::NativeConstruct()
{
	SetCountdownState(ECountdownState::None);
}

void UMiniGameReadyCountdown::SetCountdownState(ECountdownState state)
{
	if (!uReadyWidget || !uGoWidget || !uThreeWidget || !uTwoWidget || !uOneWidget) return;

	uReadyWidget->SetVisibility(ESlateVisibility::Hidden);
	uGoWidget->SetVisibility(ESlateVisibility::Hidden);
	uThreeWidget->SetVisibility(ESlateVisibility::Hidden);
	uTwoWidget->SetVisibility(ESlateVisibility::Hidden);
	uOneWidget->SetVisibility(ESlateVisibility::Hidden);

	switch (state)
	{
	case ECountdownState::Ready:	uReadyWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case ECountdownState::Three:	uThreeWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case ECountdownState::Two:		uTwoWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case ECountdownState::One:		uOneWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	case ECountdownState::Go:		uGoWidget->SetVisibility(ESlateVisibility::Visible);
		break;
	}
}

bool UMiniGameReadyCountdown::NextCountdownState(ECountdownState& state)
{
	bool bFinished = false;

	switch (state)
	{
	case ECountdownState::None:		state = ECountdownState::Ready;
		break;
	case ECountdownState::Ready:	state = ECountdownState::Three;
		break;
	case ECountdownState::Three:	state = ECountdownState::Two;
		break;
	case ECountdownState::Two:		state = ECountdownState::One;
		break;
	case ECountdownState::One:		state = ECountdownState::Go;
		break;
	case ECountdownState::Go:
	{		
		state = ECountdownState::None;
		bFinished = true;
	}
		break;
	}

	SetCountdownState(state);

	return bFinished;
}