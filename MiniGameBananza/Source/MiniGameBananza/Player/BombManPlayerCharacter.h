// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "BombManPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPlayerCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float PlayerMovementStep = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float PlayerMovementSpeed = 50.0f;

private:

	FVector TargetPosition;
	bool bIsMoving;
};
