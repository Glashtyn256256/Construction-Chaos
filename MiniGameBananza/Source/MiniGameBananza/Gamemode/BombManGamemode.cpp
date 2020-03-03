// Fill out your copyright notice in the Description page of Project Settings.
// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManGamemode.h"
#include "MiniGameBananza/Player/BombManPlayerCharacter.h"
#include "Core/Public/Misc/AssertionMacros.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MiniGameBananza/Player/BombManPlayerController.h"

void ABombManGamemode::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}
