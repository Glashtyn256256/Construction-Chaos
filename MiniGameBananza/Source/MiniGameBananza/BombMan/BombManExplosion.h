// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/Classes/Sound/SoundCue.h"
#include "Particles/ParticleSystemComponent.h"
#include "BombManCollision.h"
#include "BombManExplosion.generated.h"

class ABombManPlayerController;

UCLASS()
class MINIGAMEBANANZA_API ABombManExplosion : public ABombManCollision
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombManExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	void HandleExplosion(float DeltaTime);

	void HandleFadeOut();

public:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly, Category = "Sphere Component")
	USphereComponent* SphereComponent;

	UPROPERTY(EditAnywhere, Category = "Particle System Component")
	UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	float Length = 400.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
	float Speed = 300.0f;

private:
	FVector StartLocation;
	bool StopExplosion;
	
	UPROPERTY()
	ABombManPlayerController* BombPlanter;

	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Audio")
	TArray<USoundCue*> ExplosionSoundCues;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetBombPlanter(ABombManPlayerController* _BombPlanter);
};
