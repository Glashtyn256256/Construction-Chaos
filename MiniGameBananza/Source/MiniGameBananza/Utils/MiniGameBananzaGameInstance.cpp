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

void UMiniGameBananzaGameInstance::SetGameMode(int gamemode) 
{

	const UWorld* World = GetWorld();
	//UGameplayStatics::OpenLevel(World, FName(TEXT("Bomberman_New")));
	if (World)
	{
		CurrentLevel = static_cast<GameModeLevels>(gamemode);
		GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::FromInt(CurrentLevel));
		switch (CurrentLevel)
		{
		case Bomberman: UGameplayStatics::OpenLevel(World, FName(TEXT("Bomberman_New")));
			break;
		case FloorIsLava: UGameplayStatics::OpenLevel(World, FName(TEXT("FloorIsLava")));
			break;
		case GirderWipeout: UGameplayStatics::OpenLevel(World, FName(TEXT("SpinnyPole")));
			break;
		}
	}
}

void UMiniGameBananzaGameInstance::NextGameMode()
{
	const UWorld* World = GetWorld();

	if (World)
	{
		CurrentLevel;

		switch (CurrentLevel)
		{
		case Bomberman: 
			CurrentLevel = FloorIsLava;
			UGameplayStatics::OpenLevel(World, FName(TEXT("FloorIsLava")));
			break;
		case FloorIsLava:
			CurrentLevel = GirderWipeout;
			UGameplayStatics::OpenLevel(World, FName(TEXT("SpinnyPole")));
			break;
		//GirderWipeout:  UGameplayStatics::OpenLevel(World, FName(TEXT("PodiumScoreboard etc")));
		case GirderWipeout:  UGameplayStatics::OpenLevel(World, FName(TEXT("Main_Menu")));
		break;
		}
	}
}