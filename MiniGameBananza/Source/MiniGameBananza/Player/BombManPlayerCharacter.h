// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"

#include "PlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/PrimitiveComponent.h"
#include "MiniGameBananza/BombMan/BombManBlock.h"
#include "MiniGameBananza/BombMan/BombManBomb.h"
#include "MiniGameBananza/BombMan/IBombManCollision.h"
#include "BombManPlayerCharacter.generated.h"

/**
 *
 */
UCLASS()
class MINIGAMEBANANZA_API ABombManPlayerCharacter : public APlayerCharacter, public IIBombManCollision
{
	GENERATED_BODY()

public:
	ABombManPlayerCharacter();

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	bool IsMoving() const;

	void HitByBomb(bool Suicide);
	void EnemyPlayerHitByMyBomb();

#pragma region IBombManCollision
	virtual bool IsPlayerCollide() const;
	virtual void SetPlayerCollide(bool _bPlayerCollide);
	virtual bool CanBeDestroyed() const;
	virtual void SetCanBeDestroyed(bool _bCanBeDestroyed);
#pragma endregion
protected:
	virtual void OnInteract() override;

private:
	bool CannotPass(FVector direction, float size);

	UFUNCTION(BlueprintCallable)
		void PlantBomb(bool ArmedByDefault = true);

	UFUNCTION(BlueprintCallable)
		void OnBombDetonation(ABombManBomb* Bomb);

public:
	UPROPERTY(EditDefaultsOnly, Category = "Bomb")
		TSubclassOf<ABombManBomb> BombToSpawn;

	UPROPERTY(EditDefaultsOnly, Category = "Bomb")
		int BombPlacementLimit = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		USphereComponent* SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float PlayerMovementStep = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float PlayerMovementSpeed = 500.0f;

private:
	TArray<ABombManBomb*> PlacedBombs;
	FVector TargetPosition;
	FVector PreviousPosition;
	bool bIsMoving;
	bool bPlayerCollide = true;
	bool bCanBeDestroyed = false;
};
