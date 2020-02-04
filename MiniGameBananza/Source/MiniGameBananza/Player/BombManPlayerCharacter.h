// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

#include "PlayerCharacter.h"
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
	float PlayerMovementStep = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float PlayerMovementSpeed = 50.0f;

private:
	TArray<ABombManBomb *> PlacedBombs;


	FVector TargetPosition;
	bool bIsMoving;
};
