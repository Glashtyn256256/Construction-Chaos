// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "Components/SphereComponent.h"
#include "MiniGameBananza/FloorIsLava/FloorIsLava_Floor_Block.h"
#include "DrawDebugHelpers.h"
#include "FloorIsLavaPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AFloorIsLavaPlayerCharacter : public AMiniGamePlayerCharacter
{
	GENERATED_BODY()
	
public:
	AFloorIsLavaPlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual FVector GetAnimVelocity() const override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void PreventCharacterStandingStill(float DeltaTime);

public:

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		float MovementSpeed = 60.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Sphere Collider")
		USphereComponent* SphereCollider;

	UPROPERTY(EditDefaultsOnly, Category = "Block Detection")
	AFloorIsLava_Floor_Block* PreviousHitBlock;


private:
	float SphereRadius, Timer, MaxTimer;
	FVector Velocity;
};
