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
#include "TimerManager.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"
#include "MiniGameBananza/UI/Generic/MiniGameReadyCountdown.h"

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
				AMiniGamePlayerCharacter* character = Cast<AMiniGamePlayerCharacter>(playerController->GetCharacter());	
				if (character)
				{
					character->RemoveRespawnProtection();
				}
			}
		}
	}

	if (bOverrideCountdown)
	{
		bCountdownEnded = true;
	}
	else
	{
		countdownState = ECountdownState::None;

		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.0f);
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

	if (!GameHUD)
	{
		GameHUD = AMiniGameHUD::GetInstance();
	}

	if (GameHUD)
	{
		if (!bCountdownEnded)
		{
			CountdownTick(DeltaSeconds);
		}
	}
}

void AMiniGameBananzaGameModeBase::CountdownTick(float DeltaSeconds)
{
	if (!GetWorld()) return;

	UMiniGameReadyCountdown* Countdown = GameHUD->GetMiniGameCountdown();

	if (!Countdown)
		return;

	float undilatedDeltaTime = DeltaSeconds / UGameplayStatics::GetGlobalTimeDilation(GetWorld());

	countdownTime += undilatedDeltaTime;

	if (countdownTime >= 1.0)
	{
		countdownTime = 0.0f;
		bCountdownEnded = Countdown->NextCountdownState(countdownState);
	}

	if (bCountdownEnded)
	{
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	}
}

void AMiniGameBananzaGameModeBase::RestartPlayer(AController* NewPlayer)
{
	AMiniGamePlayerController* PlayerController = Cast<AMiniGamePlayerController>(NewPlayer);

	UWorld* world = GetWorld();
	if (PlayerController && world)
	{
		const AActor* playerStart = GetSpawnPoint(PlayerController);
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
				else if (localPlayerid < CharacterClasses.Num())
				{
					PlayerPrefab = CharacterClasses[localPlayerid];
				}
			}

			// Respawn new pawn for player			// Note: GetDefaultPawnClassForController(PlayerController) is the override if needed
			APawn* actor = world->SpawnActor<APawn>(PlayerPrefab, spawnLocation, spawnRotation, spawnParams);
			if (actor)
			{
				PlayerController->SetPawn(actor);
				OnCharacterSpawned(PlayerController, actor);
			}
			FinishRestartPlayer(NewPlayer, spawnRotation);
		}
	}
}

void AMiniGameBananzaGameModeBase::OnCharacterSpawned(AController* Controller, APawn* Pawn)
{

}

AActor* AMiniGameBananzaGameModeBase::GetSpawnPoint(AMiniGamePlayerController* Controller)
{
	return FindPlayerStart(Controller);
}

void AMiniGameBananzaGameModeBase::OnDead(AMiniGamePlayerController* Controller)
{
	if (!Controller || bGamemodeEnded) return;

	TArray<AMiniGamePlayerController*> DeadControllers;
	TArray<AMiniGamePlayerController*> AliveControllers;
	FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator();
	if (Iterator)
	{
		for (Iterator; Iterator; ++Iterator)
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
	}
	int DeadCount = DeadControllers.Num();

	Controller->UpdateScore(DeadCount);

	// Update last person alive score
	if (AliveControllers.Num() == 1)
	{
		bGamemodeEnded = true;
		AMiniGamePlayerController* AliveController = AliveControllers[0];
		if (AliveController)
		{
			AliveController->UpdateScore(DeadCount + 1);
			DisplayAllPlayersScore();
		}
		FTimerHandle GamemodeTimeHandle;
		GetWorldTimerManager().SetTimer(GamemodeTimeHandle, this, &AMiniGameBananzaGameModeBase::OnGamemodeFinished, 5.0f, false);
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

void AMiniGameBananzaGameModeBase::DisplayAllPlayersScore() {
	FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator();
	if (Iterator)
	{
		for (Iterator; Iterator; ++Iterator)
		{
			AMiniGamePlayerController* PlayerController = Cast<AMiniGamePlayerController>(Iterator->Get());
			if (PlayerController)
			{
				PlayerController->MiniGamePlayerUI->SetScoreUI(PlayerController->GetScore());
			}
		}
	}
}

bool AMiniGameBananzaGameModeBase::IsCountdownActive() const
{
	return !bCountdownEnded;
}

bool AMiniGameBananzaGameModeBase::IsGamemodeActive() const
{
	return !bGamemodeEnded;
}
