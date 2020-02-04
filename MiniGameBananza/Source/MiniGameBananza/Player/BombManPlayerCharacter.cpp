// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerCharacter.h"
#include "Components/InputComponent.h"

#include "GameFramework/Actor.h"

ABombManPlayerCharacter::ABombManPlayerCharacter()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (SphereComponent)
	{
		SphereComponent->AttachTo(RootComponent);
	}
}

void ABombManPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (SphereComponent)
	{
		SphereComponent->SetSphereRadius(PlayerMovementStep * 0.4f);
	}

	PreviousPosition = TargetPosition = GetActorLocation();
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
			TArray<UPrimitiveComponent*> overlapping;
			SphereComponent->SetWorldLocation(GetActorLocation() + GetActorForwardVector() * PlayerMovementStep * ForwardDir);
			SphereComponent->GetOverlappingComponents(overlapping);

			if (ContainsWall(overlapping))
				bCanMoveForward = false;
		}

		if (bCanMoveRight)
		{
			TArray<UPrimitiveComponent*> overlapping;
			SphereComponent->SetWorldLocation(GetActorLocation() + GetActorRightVector() * PlayerMovementStep * RightDir);
			SphereComponent->GetOverlappingComponents(overlapping);

			if (ContainsWall(overlapping))
				bCanMoveRight = false;
		}

		if (bCanMoveForward)
		{
			PreviousPosition = TargetPosition;
			TargetPosition = GetActorLocation();
			TargetPosition += GetActorForwardVector() * PlayerMovementStep * ForwardDir;
			bIsMoving = true;
		}
		else if (bCanMoveRight)
		{
			PreviousPosition = TargetPosition;
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
			PreviousPosition = TargetPosition;
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
bool ABombManPlayerCharacter::ContainsWall(TArray<UPrimitiveComponent*> overlaps)
{
	for (UPrimitiveComponent* component : overlaps)
	{
		if (!component->GetAttachmentRootActor() || !Cast<APlayerCharacter>(component->GetAttachmentRootActor()))
			return true;
	}

	return false;
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
	FVector spawnLocation = PreviousPosition;
	FRotator spawnRotation = GetActorRotation();

	for (ABombManBomb * bomb : PlacedBombs)
	{
		if (FVector::Dist(bomb->GetActorLocation(), spawnLocation) < 1.0f)
		{
			return;
		}
	}

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

bool ABombManPlayerCharacter::IsMoving() const
{
	return bIsMoving;
}