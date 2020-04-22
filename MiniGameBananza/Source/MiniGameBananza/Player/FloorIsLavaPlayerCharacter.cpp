// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/Character.h"
#include "FloorIsLavaPlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"

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

FVector AFloorIsLavaPlayerCharacter::GetAnimVelocity() const
{
	return Velocity * 10.0f;
}