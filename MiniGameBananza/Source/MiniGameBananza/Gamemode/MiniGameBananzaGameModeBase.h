// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGameBananzaGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMiniGameBananzaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Local Multiplayer")
	int PlayerCount = 4;
};
