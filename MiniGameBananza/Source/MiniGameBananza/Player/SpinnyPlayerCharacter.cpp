// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyPlayerCharacter.h"
#include "SpinnyPlayerController.h"
#include "MiniGameBananza/Spinny/SpinnyPole.h"
#include "MiniGameBananza/Gamemode/SpinnyGamemode.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/WorldSettings.h"
#include "MiniGameBananza/Gamemode/MiniGameBananzaGameModeBase.h"


ASpinnyPlayerCharacter::ASpinnyPlayerCharacter()
{
	bPoleHasPassed = false;
}

void ASpinnyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRagdoll)
	{
		USkeletalMeshComponent* MeshLocal = GetMesh();
		if (MeshLocal)
		{
			SetActorLocation(MeshLocal->GetComponentLocation());
		}
	}

	if (GetJump())
	{
		jumpAnimTime += DeltaTime;

		if (jumpAnimTime >= 1.0f)
		{
			SetJump(false);
		}
	}

	if (bDead)
	{
		deadTime += DeltaTime;

		if (deadTime >= 2.5f && GetWorld())
		{
			deadTime = 0.0f;
			Destroy();
		}
	}
}

void ASpinnyPlayerCharacter::Destroyed()
{
	// Get the controller before Super::Destroyed() is called, otherwise it is NULL.
	ASpinnyPlayerController* thisController = Cast<ASpinnyPlayerController>(this->GetController());

	Super::Destroyed();

	AMiniGameBananzaGameModeBase* gamemode = Cast<AMiniGameBananzaGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode && thisController)
	{
		thisController->StartRespawnProcess();
		thisController->SetViewTargetWithBlend(gamemode->CameraActor);
	}
}

bool ASpinnyPlayerCharacter::HasRespawnProtection() const
{
	ASpinnyGamemode* gamemode = Cast<ASpinnyGamemode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (gamemode && gamemode->PoleIsFast())
	{
		return !bPoleHasPassed;
	}
	return Super::HasRespawnProtection();
}

void ASpinnyPlayerCharacter::RemoveRespawnProtection()
{
	Super::RemoveRespawnProtection();

	bPoleHasPassed = true;
}

void ASpinnyPlayerCharacter::OnJump()
{
	if (GetJump()) return;

	ACharacter::Jump();

	jumpAnimTime = 0.0f;

	SetJump(true);
}

void ASpinnyPlayerCharacter::HandleRespawnProtection(float DeltaTime)
{
	Super::HandleRespawnProtection(DeltaTime);

}

bool ASpinnyPlayerCharacter::IsCollidingWithPole() const
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, ASpinnyPole::StaticClass());
	if (overlappingActors.Num() > 0)
	{
		return true;
	}
	return false;
}

void ASpinnyPlayerCharacter::Die(FVector force)
{
	// Push into killZ
	Ragdoll(force);
	bDead = true;
	deadTime = 0.0f;
}