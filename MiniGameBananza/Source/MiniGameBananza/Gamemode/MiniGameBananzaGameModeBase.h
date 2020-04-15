// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGameBananza/UI/HUD/MiniGameHUD.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "MiniGameBananzaGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMiniGameBananzaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:

	virtual void RestartPlayer(AController * NewPlayer) override;

protected:
	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
public:
	UPROPERTY(EditDefaultsOnly, Category = "Local Multiplayer")
	int PlayerCount = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Local Multiplayer")
	TArray<TSubclassOf<AMiniGamePlayerCharacter>> CharacterClasses;

	AActor* CameraActor;
};
