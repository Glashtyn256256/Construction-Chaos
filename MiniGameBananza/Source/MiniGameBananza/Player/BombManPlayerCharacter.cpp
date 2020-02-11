// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerCharacter.h"
#include "Components/InputComponent.h"

#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

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
			if (CannotPass(GetActorForwardVector(), PlayerMovementStep * ForwardDir))
				bCanMoveForward = false;
		}

		if (bCanMoveRight)
		{
			if (CannotPass(GetActorRightVector(), PlayerMovementStep * RightDir))
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
			if (CannotPass(FVector::ZeroVector, 0.0f))
			{
				bIsMoving = false;
				SetActorLocation(PreviousPosition);
				TargetPosition = PreviousPosition;
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
}
bool ABombManPlayerCharacter::CannotPass(FVector direction, float size)
{
	if (!SphereComponent) return false;

	TArray<UPrimitiveComponent*> overlapping;
	SphereComponent->SetWorldLocation(GetActorLocation() + direction * size);
	SphereComponent->GetOverlappingComponents(overlapping);
	SphereComponent->SetWorldLocation(GetActorLocation());

	for (UPrimitiveComponent* Prim : overlapping)
	{
		IIBombManCollision* Collision = Cast<IIBombManCollision>(Prim->GetAttachmentRootActor());
		if (Collision && Collision->IsPlayerCollide())
		{
			AActor* ActorCollision = Cast<AActor>(Collision);

			if (ActorCollision && ActorCollision != this)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					1.0f,
					FColor::Cyan,
					FString::Printf(TEXT("CanPass::true %s"), *ActorCollision->GetName()));
				return true;
			}
		}
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

void ABombManPlayerCharacter::HitByBomb(bool Suicide)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("ABombManPlayerCharacter::HitByBomb")));
}

void ABombManPlayerCharacter::EnemyPlayerHitByMyBomb()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("ABombManPlayerCharacter::EnemyPlayerHitByMyBomb")));
}

void ABombManPlayerCharacter::PlantBomb(bool ArmedByDefault)
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
		bomb->SetBombPlanter(this);
		if (ArmedByDefault)
		{
			bomb->Arm();
		}

		bomb->OnBombExplode.AddUObject(this, &ABombManPlayerCharacter::OnBombDetonation);
		PlacedBombs.Add(bomb);
	}
}

void ABombManPlayerCharacter::OnBombDetonation(ABombManBomb* Bomb)
{
	PlacedBombs.Remove(Bomb);
}

bool ABombManPlayerCharacter::IsMoving() const
{
	return bIsMoving;
}

#pragma region IBombManCollision
bool ABombManPlayerCharacter::IsPlayerCollide() const
{
	return bPlayerCollide;
}
void ABombManPlayerCharacter::SetPlayerCollide(bool _bPlayerCollide)
{
	this->bPlayerCollide = _bPlayerCollide;
}
bool ABombManPlayerCharacter::CanBeDestroyed() const
{
	return bCanBeDamaged;
}
void ABombManPlayerCharacter::SetCanBeDestroyed(bool _bCanBeDestroyed)
{
	this->bCanBeDestroyed = _bCanBeDestroyed;
}
#pragma endregion