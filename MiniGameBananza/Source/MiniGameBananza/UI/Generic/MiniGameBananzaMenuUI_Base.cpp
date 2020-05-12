// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameBananzaMenuUI_Base.h"

void UMiniGameBananzaMenuUI_Base::NativeConstruct()
{
	Super::NativeConstruct();

	MiniGameInstance = Cast<UMiniGameBananzaGameInstance>(GetGameInstance());

	InitializeComponents();
}

void UMiniGameBananzaMenuUI_Base::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	HandleAction(DeltaTime);

	HandleMusicLoop(DeltaTime);
}

void UMiniGameBananzaMenuUI_Base::InitializeComponents()
{
}

void UMiniGameBananzaMenuUI_Base::OnHoverButton()
{
	if (scHover)
	{
		PlaySound(scHover);
	}
}

void UMiniGameBananzaMenuUI_Base::OnClickButton()
{
	if (scClick_High)
	{
		PlaySound(scClick_High);
	}
}

void UMiniGameBananzaMenuUI_Base::OnClickBackButton()
{
	if (scClick_Low)
	{
		PlaySound(scClick_Low);
	}
}

void UMiniGameBananzaMenuUI_Base::HandleAction(float DeltaTime)
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

void UMiniGameBananzaMenuUI_Base::HandleMusicLoop(float DeltaTime)
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

void UMiniGameBananzaMenuUI_Base::PlaySoundAndActionWhenFinished(USoundBase* SoundBase, FOnAction action)
{
	if (SoundBase && !OnUIAction.IsBound())
	{
		ActionTimer = SoundBase->GetDuration();
		OnUIAction = action;
		PlaySound(SoundBase);
	}
}