// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"
#include "Containers/Array.h"
#include "BombManCollision.h"

#include "BombManExplosion.h"
#include "BombManBomb.generated.h"

class ABombManPlayerCharacter;


#pragma region Delegate Decl

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBombDetonation, ABombManBomb *)

#pragma endregion

UCLASS()
class MINIGAMEBANANZA_API ABombManBomb : public ABombManCollision
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombManBomb();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Arm();
	void Defuse();
	void Reset();
	bool IsOverlapping() const;

	void SetCountdownModifier(float Value);

	void Explode();
	void HandleExplode(float DeltaTime);

	void HandleGrow(float DeltaTime);

	void SetBombPlanter(ABombManPlayerCharacter* _BombPlanter);

protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);

private:
	void CreateExplosion();

public:
	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	USphereComponent* SphereComponent;

	// Allows you to click and drag blueprints in the inspector (like spawning prefabs in unity)
	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	TSubclassOf<ABombManExplosion> ExplosionToSpawn;

	// How long it takes for the bomb to explode when armed
	UPROPERTY(EditDefaultsOnly)
	float StartingDetonationTime = 4.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Growth Animation")
	float GrowthTime = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Growth Animation")
	FVector MaximumScale = FVector::OneVector;

	UPROPERTY(EditDefaultsOnly, Category = "Growth Animation")
	FVector MinimumScale = FVector(0.025f, 0.025f, 0.025f);

	// Delegate
	FOnBombDetonation OnBombDetonation;

private:
	bool IsArmed;
	float TimeUntilDetonation;
	float CountdownModifier;
	float GrowthProgress;
	bool bStartGrowing;
	bool bExploded = false;

	ABombManPlayerCharacter* BombPlanter;

};
