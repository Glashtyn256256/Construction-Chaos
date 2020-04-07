// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MiniGameBananzaGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Core/Public/Misc/AssertionMacros.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

void AMiniGameBananzaGameModeBase::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	const UWorld* world = GetWorld();
	if (world)
	{
		TArray<APlayerController*> playerControllers;
		for (int i = 0; i <= PlayerCount; ++i)
		{
			APlayerController* PlayerController = UGameplayStatics::CreatePlayer(world, i);
			if (PlayerController)
			{
				playerControllers.Add(PlayerController);
			}
		}

		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(world, ACameraActor::StaticClass(), foundActors);

		if (foundActors.Num() > 0)
		{
			CameraActor = foundActors[0];
		}


		for (AActor* actor : foundActors)
		{
			TArray< UActorComponent*> validComponents = actor->GetComponentsByTag(UActorComponent::StaticClass(), TEXT("MainCamera"));
			if (validComponents.Num() > 0)
			{
				CameraActor = actor;
			}
		}

		for (APlayerController* playerController : playerControllers)
		{
			if (playerController && CameraActor)
			{
				playerController->SetViewTargetWithBlend(CameraActor);
			}
		}
	}
}

void AMiniGameBananzaGameModeBase::RestartPlayer(AController * NewPlayer)
{
	APlayerController* PlayerController = Cast<APlayerController>(NewPlayer);

	UWorld* world = GetWorld();
	if (PlayerController && world)
	{
		const AActor* playerStart = FindPlayerStart(PlayerController);
		if (playerStart)
		{
			const FVector spawnLocation = playerStart->GetTransform().GetLocation();
			const FRotator spawnRotation = playerStart->GetActorRotation();
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
			APawn* actor = world->SpawnActor<APawn>(GetDefaultPawnClassForController(PlayerController), spawnLocation, spawnRotation, spawnParams);
			if (actor)
			{
				PlayerController->SetPawn(actor);
			}
			FinishRestartPlayer(NewPlayer, spawnRotation);
		}
	}

}

void AMiniGameBananzaGameModeBase::FinishRestartPlayer(AController* NewPlayer, const FRotator& StartRotation)
{
	Super::FinishRestartPlayer(NewPlayer, StartRotation);

	APlayerController* PlayerController = Cast<APlayerController>(NewPlayer);

	if (PlayerController && CameraActor)
	{
		PlayerController->SetViewTargetWithBlend(CameraActor);
	}
}
