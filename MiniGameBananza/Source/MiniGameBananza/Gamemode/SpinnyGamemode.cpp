// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyGamemode.h"
#include "MiniGameBananza/Player/SpinnyPlayerController.h"
#include "MiniGameBananza/UI/HUD/SpinnyMiniGameHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

void ASpinnyGamemode::BeginPlay()
{
	SpeedLevel = 1;

	const UWorld* world = GetWorld();
	if (world)
	{
		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(world, ASpinnyPole::StaticClass(), foundActors);
		if (foundActors.Num() > 0)
		{
			SpinnyPole = Cast<ASpinnyPole>(foundActors[0]);
		}
	}
}

void ASpinnyGamemode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpinnyPole)
	{
		if (SpinnyPole->CurrentRotationSpeed >= SpinnyPole->PreviousRotationSpeed + SpeedPerLevelIncrement)
		{
			IncrementSpeedLevel();
			SpinnyPole->PreviousRotationSpeed = SpinnyPole->CurrentRotationSpeed;
		}
	}
}

int ASpinnyGamemode::GetSpeedLevel() const
{
	return SpeedLevel;
}

void ASpinnyGamemode::IncrementSpeedLevel()
{
	const UWorld* world = GetWorld();
	if (world)
	{
		ASpinnyPlayerController* controller = Cast<ASpinnyPlayerController>(world->GetFirstPlayerController());
		if (controller)
		{
			ASpinnyMiniGameHUD* hud = Cast<ASpinnyMiniGameHUD>(controller->GetHUD());
			if (hud)
			{
				hud->SetSpeedLevel(++SpeedLevel);
			}
		}
	}
}

bool ASpinnyGamemode::PoleIsFast() const
{
	return SpeedLevel > 15;
}
