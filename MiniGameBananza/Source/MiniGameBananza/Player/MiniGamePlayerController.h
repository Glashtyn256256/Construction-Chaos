// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MiniGameBananza/UI/Generic/MiniGamePlayerUI.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"
#include "MiniGamePlayerController.generated.h"

class AMiniGamePlayerCharacter;
class AMiniGameHUD;

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMiniGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime) override;

	AMiniGameHUD* GetMiniGameHUD();

	void StartRespawnProcess();

	UFUNCTION()
	void SetNumLives(int lives);
	int GetLives() const;
	bool HasRanOutOfLives() const;

	void UpdateScore(int score) const;
	int GetScore() const;

protected:
	virtual void Respawn();
	virtual void OnDead();

	void CheckHUD();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	int MaxLives = 3;

	UPROPERTY()
	UMiniGamePlayerUI* MiniGamePlayerUI;
protected:


	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float MaxRespawnTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float RespawnCountdownModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	int NumLives = MaxLives;

private:
	float RespawnCountdownTimer;
	bool bIsRespawning;
	
};
