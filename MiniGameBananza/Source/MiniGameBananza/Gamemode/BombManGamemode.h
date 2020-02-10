// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "MiniGameBananzaGameModeBase.h"
#include "BombManGamemode.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManGamemode : public AMiniGameBananzaGameModeBase
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

public:

	// Temporary
	UPROPERTY(EditDefaultsOnly, Category = "Local Multiplayer")
	int PlayerCount = 1;

};
