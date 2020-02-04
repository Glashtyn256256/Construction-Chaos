// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerCharacter.h"
#include "Components/InputComponent.h"

#include "GameFramework/Actor.h"

ABombManPlayerCharacter::ABombManPlayerCharacter()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->AttachTo(RootComponent);
}

void ABombManPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SphereComponent->SetSphereRadius(PlayerMovementStep * 0.4f);

	TargetPosition = GetActorLocation();
}

void ABombManPlayerCharacter::Tick(float DeltaTime)
{
	if (!bIsMoving)
	{
		int ForwardDir = InputForward;
		int RightDir = InputRight;

		bool bCanMoveForward = ForwardDir != 0;
		bool bCanMoveRight = RightDir != 0;

		if (bCanMoveForward)
		{
			TArray<AActor*> overlapping;
			SphereComponent->SetWorldLocation(GetActorLocation() + GetActorForwardVector() * PlayerMovementStep * ForwardDir);
			SphereComponent->GetOverlappingActors(overlapping, ABombManBlock::StaticClass());

			if (overlapping.Num() > 0)
				bCanMoveForward = false;
		}

		if (bCanMoveRight)
		{
			TArray<AActor*> overlapping;
			SphereComponent->SetWorldLocation(GetActorLocation() + GetActorRightVector() * PlayerMovementStep * RightDir);
			SphereComponent->GetOverlappingActors(overlapping, ABombManBlock::StaticClass());

			if (overlapping.Num() > 0)
				bCanMoveRight = false;
		}

		if (bCanMoveForward)
		{
			TargetPosition = GetActorLocation();
			TargetPosition += GetActorForwardVector() * PlayerMovementStep * ForwardDir;
			bIsMoving = true;
		}
		else if (bCanMoveRight)
		{
			TargetPosition = GetActorLocation();
			TargetPosition += GetActorRightVector() * PlayerMovementStep * RightDir;
			bIsMoving = true;
		}

		if (!bIsMoving)
		{
			SetActorLocation(TargetPosition);
		}

	}
	else
	{
		if (FVector::Dist(GetActorLocation(), TargetPosition) <= 5.0f)
		{
			bIsMoving = false;
			SetActorLocation(TargetPosition);
		}
		else
		{
			FVector position = GetActorLocation();

			FVector targetDirection = (TargetPosition - position).GetSafeNormal();

			SetActorLocation(position + targetDirection * PlayerMovementSpeed * GetWorld()->DeltaTimeSeconds);
			//AddMovementInput(targetDirection * PlayerMovementSpeed);
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