// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayersUI.h"

UMiniGamePlayerUI* UMiniGamePlayersUI::GetMiniGamePlayerUI(APlayerController* Controller)
{
	if (!Controller || !Controller->GetLocalPlayer()) return nullptr;

	switch (Controller->GetLocalPlayer()->GetControllerId())
	{
	case 0: return PlayerUI_0;
	case 1: return PlayerUI_1;
	case 2: return PlayerUI_2;
	case 3: return PlayerUI_3;
	}

	return nullptr;
}