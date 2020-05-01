// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyMiniGameUI.h"

void USpinnyMiniGameUI::SetSpeedLevel(int speedLevel)
{
	if (SpeedLevel)
	{
		SpeedLevel->SetText(FText::FromString(TEXT("Speed Level ") + FString::FromInt(speedLevel)));
	}
}
