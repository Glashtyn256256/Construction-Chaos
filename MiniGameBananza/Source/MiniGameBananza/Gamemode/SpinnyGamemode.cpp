// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

ASpinnyGamemode::ASpinnyGamemode() : SpeedLevel(1)
{
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
	SpeedLevel++;

	// TODO: UI Update
}

bool ASpinnyGamemode::PoleIsFast() const
{
	return SpeedLevel > 10;
}
