// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyPlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASpinnyPlayerCharacter::OnJump()
{
	ACharacter::Jump();
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