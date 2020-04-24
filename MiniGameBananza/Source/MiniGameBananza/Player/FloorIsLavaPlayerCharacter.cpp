// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorIsLavaPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "MiniGameBananza/Player/FloorIsLavaPlayerController.h"
#include "MiniGameBananza/Gamemode/FloorIsLavaGamemode.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

	// Called every frame
void AFloorIsLavaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Velocity = (GetActorForwardVector() * InputForward) + (GetActorRightVector() * InputRight);
	Velocity *= MovementSpeed * DeltaTime;

	AddMovementInput(Velocity, 1.0f);

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent && Velocity.Size() >= 0.1f)
	{
		FRotator Rotation = FRotator(Velocity.Rotation());
		Rotation.Add(0.0f, 270.0f, 0.0f);

		FRotator CurrentRotation = MeshComponent->GetRelativeRotation();

		FQuat SmoothRotation = FQuat::Slerp(CurrentRotation.Quaternion(), Rotation.Quaternion(), DeltaTime * 20.0f);

		MeshComponent->SetRelativeRotation(SmoothRotation.Rotator());
	}
}

float AFloorIsLavaPlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
		AFloorIsLavaPlayerController* LavaController = Cast<AFloorIsLavaPlayerController>(Controller);
		if (LavaController)
		{
			Destroy();
			LavaController->StartRespawnProcess();
			AMiniGameBananzaGameModeBase* gamemode = Cast<AMiniGameBananzaGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (gamemode)
			{
				LavaController->SetViewTargetWithBlend(gamemode->CameraActor);
			}
		}

		return Damage;
}

FVector AFloorIsLavaPlayerCharacter::GetAnimVelocity() const
{
	return Velocity * 10.0f;
}