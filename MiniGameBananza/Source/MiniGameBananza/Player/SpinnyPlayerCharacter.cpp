// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyPlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASpinnyPlayerCharacter::Tick(float DeltaTime)
{
	if (GetJump())
	{
		jumpAnimTime += DeltaTime;

		if (jumpAnimTime >= 1.0f)
		{
			SetJump(false);
		}
	}
}

void ASpinnyPlayerCharacter::OnJump()
{
	if (GetJump()) return;

	ACharacter::Jump();

	jumpAnimTime = 0.0f;

	SetJump(true);
}

void ASpinnyPlayerCharacter::Die(FVector force)
{
	USkeletalMeshComponent* MeshLocal = GetMesh();
	if (MeshLocal)
	{
		GetCharacterMovement()->DisableMovement();
		MeshLocal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshLocal->SetAllBodiesSimulatePhysics(true);
		MeshLocal->AddForceToAllBodiesBelow(force);
	}
}