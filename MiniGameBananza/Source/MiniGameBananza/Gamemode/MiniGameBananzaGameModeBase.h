// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MiniGameBananza/UI/HUD/MiniGameHUD.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "MiniGameBananza/Player/MiniGamePlayerController.h"
#include "MiniGameBananza/UI/HUD/MiniGameHUD.h"
#include "MiniGameBananzaGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMiniGameBananzaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMiniGameBananzaGameModeBase();
	virtual void BeginPlay() override;

public:

	virtual void RestartPlayer(AController * NewPlayer) override;
	virtual void DisplayAllPlayersScore();
	virtual void OnDead(AMiniGamePlayerController* Controller);
	virtual void Tick(float DeltaSeconds) override;
	void CountdownTick(float DeltaSeconds);
	bool IsCountdownActive() const;
	bool IsGamemodeActive() const;

protected:
	virtual AActor* GetSpawnPoint(AMiniGamePlayerController* Controller);
	virtual void OnGamemodeFinished();
	virtual void FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation) override;
	virtual void OnCharacterSpawned(AController* Controller, APawn* Pawn);
public:
	UPROPERTY(EditDefaultsOnly, Category = "Local Multiplayer")
	int PlayerCount = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Local Multiplayer")
	TArray<TSubclassOf<AMiniGamePlayerCharacter>> CharacterClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Override")
	bool bOverrideCountdown;

	AActor* CameraActor;

protected:
	bool bGamemodeEnded;
	bool bCountdownEnded;
	float countdownTime;
	ECountdownState countdownState;

	AMiniGameHUD* GameHUD;
};
