// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "MiniGameBananza/Player/BombManPlayerCharacter.h"
#include "MiniGameBananzaGameModeBase.h"
#include "BombManGamemode.generated.h"

class ABombManPlayerController;

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

	bool RespawnPlayer(ABombManPlayerController* PlayerController, bool ReplaceExisting = false);

	// Temporary
	UPROPERTY(EditDefaultsOnly, Category = "Local Multiplayer")
	int PlayerCount = 1;

private:
	TArray<TPair<FVector, FRotator>> SpawnLocations;

};
