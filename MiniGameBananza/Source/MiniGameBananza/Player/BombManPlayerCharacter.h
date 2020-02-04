// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "MiniGameBananza/BombMan/BombManBlock.h"
#include "MiniGameBananza/BombMan/BombManBomb.h"
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

protected:
	virtual void OnInteract() override;

private:
	UFUNCTION(BlueprintCallable)
	void PlantBomb(bool Armed = true);

	UFUNCTION(BlueprintCallable)
	void OnBombDetonation(ABombManBomb * Bomb);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Bomb")
	TSubclassOf<ABombManBomb> BombToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Bomb")
	int BombPlacementLimit = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly)
	float PlayerMovementStep = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float PlayerMovementSpeed = 500.0f;

private:
	TArray<ABombManBomb *> PlacedBombs;
	FVector TargetPosition;
	bool bIsMoving;
};
