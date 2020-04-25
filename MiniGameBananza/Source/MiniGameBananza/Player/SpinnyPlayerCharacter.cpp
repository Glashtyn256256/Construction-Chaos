// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyPlayerCharacter.h"
#include "SpinnyPlayerController.h"
#include "MiniGameBananza/Gamemode/MiniGameBananzaGameModeBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/WorldSettings.h"
#include "GameFramework/CharacterMovementComponent.h"

ASpinnyPlayerCharacter::ASpinnyPlayerCharacter()
{
	bHasRecentlyRespawned = true;
	RespawnProtectionTimer = MaxRespawnProtectionTime;
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

void ASpinnyPlayerCharacter::OnJump()
{
	if (GetJump()) return;

	ACharacter::Jump();

	jumpAnimTime = 0.0f;

	SetJump(true);
}

void ASpinnyPlayerCharacter::HandleRespawnProtection(float DeltaTime)
{
	// TODO: Remove protection when spinny bar has just passed us

	// Placeholder implementation using timers (like bombman)
	if (bHasRecentlyRespawned)
	{
		RespawnProtectionTimer -= DeltaTime;
		if (RespawnProtectionTimer <= 0)
		{
			bHasRecentlyRespawned = false;
		}
	}
}

void ASpinnyPlayerCharacter::Die(FVector force)
{
	// Push into killZ
	Ragdoll(force);
}

void ASpinnyPlayerCharacter::Ragdoll(FVector force)
{
	USkeletalMeshComponent* MeshLocal = GetMesh();
	if (MeshLocal)
	{
		GetCharacterMovement()->DisableMovement();
		MeshLocal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshLocal->SetAllBodiesSimulatePhysics(true);
		MeshLocal->AddForceToAllBodiesBelow(force);

		bIsRagdoll = true;
	}
}