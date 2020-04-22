// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "FloorIsLavaPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AFloorIsLavaPlayerCharacter : public AMiniGamePlayerCharacter
{
	GENERATED_BODY()
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual FVector GetAnimVelocity() const override;
public:

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MovementSpeed = 60.0f;


private:
	FVector Velocity;
};
