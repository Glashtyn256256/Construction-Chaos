// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManPlayerCharacter.h"
#include "GameFramework/Actor.h"

void ABombManPlayerCharacter::Tick(float DeltaTime)
{
	if (!bIsMoving)
	{
		int ForwardDir = InputForward;
		int RightDir = InputRight;

		if (ForwardDir != 0)
		{
			TargetPosition = GetActorLocation();
			TargetPosition += GetActorForwardVector() * PlayerMovementStep * ForwardDir;
			bIsMoving = true;
		}
		else if (RightDir != 0)
		{
			TargetPosition = GetActorLocation();
			TargetPosition += GetActorRightVector() * PlayerMovementStep * RightDir;
			bIsMoving = true;
		}

	}
	else
	{
		if (FVector::Dist(GetActorLocation(), TargetPosition) <= 5.0f)
		{
			SetActorLocation(TargetPosition);
			bIsMoving = false;
		}
		else
		{
			FVector position = GetActorLocation();

			FVector targetDirection = (TargetPosition - position).GetSafeNormal();

			AddMovementInput(targetDirection * PlayerMovementSpeed);
		}
	}
}