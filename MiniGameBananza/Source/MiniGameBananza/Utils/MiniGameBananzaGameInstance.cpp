// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGameBananzaGameInstance.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

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

void UMiniGameBananzaGameInstance::SetGameMode(GameModeLevels gamemode)
{

	UWorld* World = GetWorld();
	//UGameplayStatics::OpenLevel(World, FName(TEXT("Bomberman_New")));
	if (World)
	{
		CurrentLevel = gamemode;
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::FromInt(CurrentLevel));
		switch (CurrentLevel)
		{
			
		case Bomberman: World->ServerTravel("Bomberman_New");
			break;
		case FloorIsLava:  World->ServerTravel("FloorIsLava");
			break;
		case GirderWipeout: World->ServerTravel("SpinnyPole");
			break;
		}
	}
}

void UMiniGameBananzaGameInstance::NextGameMode()
{
	UWorld* World = GetWorld();

	if (World)
	{
		CurrentLevel;

		switch (CurrentLevel)
		{
		case Bomberman: 
			SetGameMode(FloorIsLava);
			break;
		case FloorIsLava:
			SetGameMode(GirderWipeout);
			break;
		//GirderWipeout:  UGameplayStatics::OpenLevel(World, FName(TEXT("PodiumScoreboard etc")));
		case GirderWipeout:  World->ServerTravel("Main_Menu");
		break;
		}
	}
}