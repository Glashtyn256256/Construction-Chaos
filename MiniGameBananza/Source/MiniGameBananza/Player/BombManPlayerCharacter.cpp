// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerCharacter.h"
#include "Components/InputComponent.h"

#include "GameFramework/Actor.h"

void ABombManPlayerCharacter::Tick(float DeltaTime)
{
	if (!bIsMoving)
	{
		int ForwardDir = InputForward;
		int RightDir = InputRight;

		if (ForwardDir != 0)
		{
			TargetPosition = GetActorLocation();
			TargetPosition += GetActorForwardVector() * PlayerMovementStep * ForwardDir;
			bIsMoving = true;
		}
		else if (RightDir != 0)
		{
			TargetPosition = GetActorLocation();
			TargetPosition += GetActorRightVector() * PlayerMovementStep * RightDir;
			bIsMoving = true;
		}

	}
	else
	{
		if (FVector::Dist(GetActorLocation(), TargetPosition) <= 5.0f)
		{
			SetActorLocation(TargetPosition);
			bIsMoving = false;
		}
		else
		{
			FVector position = GetActorLocation();

			FVector targetDirection = (TargetPosition - position).GetSafeNormal();

			AddMovementInput(targetDirection * PlayerMovementSpeed);
		}
	}
}

void ABombManPlayerCharacter::OnInteract()
{
	Super::OnInteract();

	if (PlacedBombs.Num() < BombPlacementLimit)
	{
		PlantBomb();
	}
}

void ABombManPlayerCharacter::PlantBomb(bool Armed)
{
	FActorSpawnParameters spawnParams;
	FVector spawnLocation = GetActorLocation();
	FRotator spawnRotation = GetActorRotation();

	ABombManBomb * bomb = GetWorld()->SpawnActor<ABombManBomb>(BombToSpawn, spawnLocation, spawnRotation, spawnParams);
	if (bomb)
	{
		if (Armed)
		{
			bomb->Arm();
		}

		bomb->BombDetonationEventHandler.BindUObject(this, &ABombManPlayerCharacter::OnBombDetonation);
		PlacedBombs.Add(bomb);
	}
}

void ABombManPlayerCharacter::OnBombDetonation(ABombManBomb * Bomb)
{
	PlacedBombs.Remove(Bomb);
}