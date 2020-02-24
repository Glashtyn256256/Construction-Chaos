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

	virtual void InitGame(const FString & MapName,const FString & Options,FString & ErrorMessage) override;

public:

	bool RespawnPlayer(ABombManPlayerController* PlayerController, bool ReplaceExisting = false);

private:
	TArray<TPair<FVector, FRotator>> SpawnLocations;

};
