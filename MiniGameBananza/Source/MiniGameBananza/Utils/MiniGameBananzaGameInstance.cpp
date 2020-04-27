// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameBananzaGameInstance.h"

void UMiniGameBananzaGameInstance::UpdateScore(int playerid, int score)
{
	FPlayerScore& PlayerScore = Scores.FindOrAdd(playerid);

	PlayerScore.score += score;
}
void UMiniGameBananzaGameInstance::ResetScores()
{
	Scores.Empty();
}
int UMiniGameBananzaGameInstance::GetScore(int playerid) const
{
	int score = 0;

	const FPlayerScore* PlayerScore = Scores.Find(playerid);
	if (PlayerScore)
	{
		score = PlayerScore->score;
	}

	return score;
}