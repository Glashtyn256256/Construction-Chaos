// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerCharacter.h"
#include "Components/InputComponent.h"
#include "BombManPlayerController.h"
#include "MiniGameBananza/Gamemode/MiniGameBananzaGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

ABombManPlayerCharacter::ABombManPlayerCharacter() : Velocity(FVector::ZeroVector)
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (SphereComponent)
	{
		SphereComponent->AttachTo(RootComponent);
	}

	ResetPlayerMovementSpeed();
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
	Super::Tick(DeltaTime);

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent && LastDirection != FVector::ZeroVector)
	{
		FRotator Rotation = FRotator(LastDirection.Rotation());

		MeshComponent->SetRelativeRotation(Rotation);
	}


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

		Velocity = FVector::ZeroVector;

		if (!bIsMoving)
		{
			SetActorLocation(TargetPosition);
		}
		else
		{
			timeTake = FVector::Dist(GetActorLocation(), TargetPosition) / p_PlayerMovementSpeed;
			time = 0.0f;
		}

	}
	else
	{
		time += DeltaTime;

		if (time >= timeTake)
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

				LastDirection = Velocity = targetDirection * p_PlayerMovementSpeed * GetWorld()->DeltaTimeSeconds;

				SetActorLocation(position + Velocity);
				//AddMovementInput(targetDirection * PlayerMovementSpeed);
			}
		}
	}
}

float ABombManPlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	ABombManPlayerController* instigatorController = Cast<ABombManPlayerController>(EventInstigator);
	ABombManExplosion* hitByExplosion = Cast<ABombManExplosion>(DamageCauser);
	if (hitByExplosion && CanDie())
	{
		ABombManPlayerController* thisController = Cast<ABombManPlayerController>(this->GetController());
		AMiniGameBananzaGameModeBase* gamemode = Cast<AMiniGameBananzaGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

		if (gamemode && thisController)
		{
			Destroy();
			thisController->StartRespawnProcess();
			thisController->SetViewTargetWithBlend(gamemode->CameraActor);
		}

		return Damage;

	}
	return 0.0f;
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
		if (Collision)
		{
			OnPlayerCollision(Collision);
			if (Collision->IsPlayerCollide())
			{
				AActor* ActorCollision = Cast<AActor>(Collision);

				if (ActorCollision && ActorCollision != this)
				{
					//GEngine->AddOnScreenDebugMessage(
					//	-1,
					//	1.0f,
					//	FColor::Cyan,
					//	FString::Printf(TEXT("CanPass::true %s"), *ActorCollision->GetName()));
					return true;
				}
			}
		}
	}

	return false;
}

void ABombManPlayerCharacter::OnPlayerCollision(IIBombManCollision* Collision)
{
	if (!Collision) return;

	Collision->OnPlayerCollision(this);
}

void ABombManPlayerCharacter::OnPlayerCollision(ABombManPlayerCharacter* Character)
{

}

void ABombManPlayerCharacter::OnInteract()
{
	Super::OnInteract();

	if (PlacedBombs.Num() < BombPlacementLimit && !HasRespawnProtection())
	{
		PlantBomb();
	}
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
		ABombManPlayerController* controller = Cast<ABombManPlayerController>(this->GetController());
		if (controller)
		{
			bomb->SetBombPlanter(controller);
			if (ArmedByDefault)
			{
				bomb->Arm();
			}

			bomb->OnBombDetonation.AddUObject(this, &ABombManPlayerCharacter::OnBombDetonation);
			PlacedBombs.Add(bomb);
		}
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

FVector ABombManPlayerCharacter::GetAnimVelocity() const
{
	return Velocity;
}

void ABombManPlayerCharacter::SetPlayerMovementSpeed(float t_PlayerMovementSpeed)
{
	this->p_PlayerMovementSpeed = t_PlayerMovementSpeed;
}

void ABombManPlayerCharacter::ResetPlayerMovementSpeed()
{
	this->p_PlayerMovementSpeed = PlayerMovementSpeed;
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