// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MiniGameBananza/UI/Generic/MiniGamePlayerUI.h"
#include "MiniGamePlayerController.generated.h"

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

	inline void StartRespawnProcess();

	void SetLives(int lives);
	int GetLives() const;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	int MaxLives = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float MaxRespawnTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	float RespawnCountdownModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawning")
	int NumLives = 3;

protected:

	UPROPERTY()
	UMiniGamePlayerUI* MiniGamePlayerUI;

private:
	float RespawnCountdownTimer;
	bool bIsRespawning;
private:
	virtual void Respawn();
	
};
