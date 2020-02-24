// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MiniGameBananzaGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void AMiniGameBananzaGameModeBase::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UWorld* const world = GetWorld();
	if (world)
	{
		for (int i = 0; i <= PlayerCount; ++i)
		{
			UGameplayStatics::CreatePlayer(world, i);
		}
	}
}