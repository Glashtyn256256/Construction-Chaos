// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "BombManExplosion.generated.h"

UCLASS()
class MINIGAMEBANANZA_API ABombManExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombManExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
		UPROPERTY(EditDefaultsOnly, Category = "Box Component")
		UBoxComponent* BoxComponent;

		UPROPERTY(EditDefaultsOnly, Category = "Particle System Component")
		UParticleSystemComponent* ParticleSystem;
		

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
