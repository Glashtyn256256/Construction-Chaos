// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MiniGameBananzaGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"
#include "Core/Public/Misc/AssertionMacros.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"

AMiniGameBananzaGameModeBase::AMiniGameBananzaGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMiniGameBananzaGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const UWorld* world = GetWorld();
	if (world)
	{
		for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
		{
			APlayerController* PlayerController = Iterator->Get();
			if (PlayerController)
			{
				UGameplayStatics::RemovePlayer(PlayerController, true);
			}
		}

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
		for (AActor* actor : foundActors)
		{
			TArray< UActorComponent*> validComponents = actor->GetComponentsByTag(UActorComponent::StaticClass(), TEXT("MainCamera"));
			if (validComponents.Num() > 0)
			{
				CameraActor = actor;
			}
			else
			{
				actor->Destroy();
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

void AMiniGameBananzaGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PlayerController = Iterator->Get();
		if (PlayerController && CameraActor)
		{
			PlayerController->SetViewTargetWithBlend(CameraActor);
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

			UClass* PlayerPrefab = GetDefaultPawnClassForController(PlayerController);

			int localPlayerid = PlayerController->GetLocalPlayer()->GetControllerId();

			if (CharacterClasses.Num() > 0)
			{
				if (localPlayerid >= CharacterClasses.Num())
				{
					PlayerPrefab = CharacterClasses[localPlayerid % CharacterClasses.Num()];
				}
				else if(localPlayerid < CharacterClasses.Num())
				{
					PlayerPrefab = CharacterClasses[localPlayerid];
				}
			}

			// Respawn new pawn for player			// Note: GetDefaultPawnClassForController(PlayerController) is the override if needed
			APawn* actor = world->SpawnActor<APawn>(PlayerPrefab, spawnLocation, spawnRotation, spawnParams);
			if (actor)
			{
				PlayerController->SetPawn(actor);
			}
			FinishRestartPlayer(NewPlayer, spawnRotation);
		}
	}
}

void AMiniGameBananzaGameModeBase::OnDead(AMiniGamePlayerController* Controller)
{
	if (!Controller) return;

	TArray<AMiniGamePlayerController*> DeadControllers;
	TArray<AMiniGamePlayerController*> AliveControllers;

	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AMiniGamePlayerController* PlayerController = Cast<AMiniGamePlayerController>(Iterator->Get());
		if (PlayerController && PlayerController != Controller)
		{
			if (PlayerController->HasRanOutOfLives())
			{
				DeadControllers.Add(PlayerController);
			}
			else
			{
				AliveControllers.Add(PlayerController);
			}
		}
	}

	int DeadCount = DeadControllers.Num();

	Controller->UpdateScore(DeadCount);

	// Update last person alive score
	if (AliveControllers.Num() == 1)
	{
		AMiniGamePlayerController* AliveController = AliveControllers[0];
		if (AliveController)
		{
			AliveController->UpdateScore(DeadCount + 1);
		}

		OnGamemodeFinished();
	}
}

void AMiniGameBananzaGameModeBase::OnGamemodeFinished()
{
	UMiniGameBananzaGameInstance* GameInstance = Cast< UMiniGameBananzaGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->NextGameMode();
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
