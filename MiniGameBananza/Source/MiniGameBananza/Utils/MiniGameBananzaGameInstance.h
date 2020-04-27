// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MiniGameBananzaGameInstance.generated.h"

struct FPlayerScore
{
	int score;
};

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API UMiniGameBananzaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void UpdateScore(int playerid,int score);
	void ResetScores();
	int GetScore(int playerid) const;


private:
	TMap<int, FPlayerScore> Scores;
};
