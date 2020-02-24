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

bool ABombManGamemode::RespawnPlayer(ABombManPlayerController* PlayerController, bool ReplaceExisting)
{
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
			if (existingPawn && ReplaceExisting)
			{
				// Destroy possessed pawn.
				PlayerController->UnPossess();
				existingPawn->Destroy();
			}
			else if (existingPawn)
			{
				// Failed to respawn the player, existing pawn is already possessed.
				return false;
			}

			// Respawn new pawn for player
			ABombManPlayerCharacter* playerCharacter = world->SpawnActor<ABombManPlayerCharacter>(PlayerController->PlayerCharacterToSpawn, spawnLocation, spawnRotation, spawnParams);
			if (playerCharacter)
			{
				PlayerController->Possess(playerCharacter);
				if (CameraActor)
				{
					PlayerController->SetViewTargetWithBlend(CameraActor);
				}
				return true;
			}
		}
	}
	return false;
}
