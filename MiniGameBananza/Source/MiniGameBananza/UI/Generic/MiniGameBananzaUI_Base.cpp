// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameBananzaUI_Base.h"

void UMiniGameBananzaUI_Base::NativeConstruct()
{
	Super::NativeConstruct();

	MiniGameInstance = Cast<UMiniGameBananzaGameInstance>(GetGameInstance());
	if (MiniGameInstance)
	{
		MiniGameInstance->SetIsGamemodeSelection(false);
	}

	InitializeComponents();
}

void UMiniGameBananzaUI_Base::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	HandleAction(DeltaTime);

	HandleMusicLoop(DeltaTime);
}

void UMiniGameBananzaUI_Base::InitializeComponents()
{
}

void UMiniGameBananzaUI_Base::OnHoverButton()
{
	if (scHover)
	{
		PlaySound(scHover);
	}
}

void UMiniGameBananzaUI_Base::OnClickButton()
{
	if (scClick_High)
	{
		PlaySound(scClick_High);
	}
}

void UMiniGameBananzaUI_Base::OnClickBackButton()
{
	if (scClick_Low)
	{
		PlaySound(scClick_Low);
	}
}

void UMiniGameBananzaUI_Base::HandleAction(float DeltaTime)
{
	if (OnUIAction.IsBound())
	{
		if (ActionTimer <= 0)
		{
			OnUIAction.Execute();
			OnUIAction.Unbind();
		}
		else
		{
			ActionTimer -= DeltaTime;
		}
	}
}

void UMiniGameBananzaUI_Base::HandleMusicLoop(float DeltaTime)
{
	if (MusicLoopTimer <= 0 && scMusic)
	{
		MusicLoopTimer = scMusic->GetDuration();
		PlaySound(scMusic);
	}
	else
	{
		MusicLoopTimer -= DeltaTime;
	}
}

void UMiniGameBananzaUI_Base::PlaySoundAndActionWhenFinished(USoundBase* SoundBase, FOnAction action)
{
	if (SoundBase && !OnUIAction.IsBound())
	{
		ActionTimer = SoundBase->GetDuration();
		OnUIAction = action;
		PlaySound(SoundBase);
	}
}