// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/Gamemode/MiniGameBananzaGameModeBase.h"
#include "WinGamemode.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AWinGamemode : public AMiniGameBananzaGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	virtual AActor* GetSpawnPoint(AMiniGamePlayerController* Controller) override;
	virtual void OnCharacterSpawned(AController* Controller, APawn* Pawn) override;

protected:
	AActor* FirstPlaceSpawn;
	AActor* SecondPlaceSpawn;
	AActor* ThirdPlaceSpawn;
	AActor* FourthPlaceSpawn;
};
