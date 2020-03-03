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

void ABombManGamemode::RestartPlayer(AController * NewPlayer)
{
	APlayerController* PlayerController = Cast<APlayerController>(NewPlayer);

	UWorld* world = GetWorld();
	if (PlayerController && world)
	{
		const AActor* playerStart = FindPlayerStart(PlayerController);
		if (playerStart)
		{
			const FVector spawnLocation = playerStart->GetTransform().GetLocation();
			const FRotator spawnRotation = playerStart->GetTransform().GetRotation().Rotator();
			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			APawn* existingPawn = PlayerController->GetPawn();
			if (existingPawn)
			{
				// Destroy possessed pawn.
				PlayerController->UnPossess();
				existingPawn->Destroy();
			}

			// Respawn new pawn for player			// Note: GetDefaultPawnClassForController(PlayerController) is the override if needed
			ABombManPlayerCharacter* playerCharacter = world->SpawnActor<ABombManPlayerCharacter>(GetDefaultPawnClassForController(PlayerController), spawnLocation, spawnRotation, spawnParams);
			if (playerCharacter)
			{
				PlayerController->SetPawn(playerCharacter);
			}
			FinishRestartPlayer(NewPlayer, spawnRotation);
		}
	}

}

void ABombManGamemode::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);

	APlayerController* PlayerController = Cast<APlayerController>(NewPlayer);

	if (PlayerController && CameraActor)
	{
		PlayerController->SetViewTargetWithBlend(CameraActor);
	}
}
