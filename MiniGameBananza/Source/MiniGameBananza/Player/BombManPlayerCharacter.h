// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "MiniGameBananza/BombMan/BombManBlock.h"
#include "BombManPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPlayerCharacter : public APlayerCharacter
{
	GENERATED_BODY()

public:
	ABombManPlayerCharacter();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	bool IsMoving() const;

private:
	bool ContainsWall(TArray<UPrimitiveComponent*> overlaps);

public:

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	float PlayerMovementStep = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float PlayerMovementSpeed = 500.0f;

private:

private:

	FVector TargetPosition;
	bool bIsMoving;
};
