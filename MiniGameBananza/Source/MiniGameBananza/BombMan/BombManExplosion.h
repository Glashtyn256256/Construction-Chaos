// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
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

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
			float Length = 400.0f;
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Variables")
			float Speed = 300.0f;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
			FVector StartLocation;
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Variables")
			FVector EndLocation;

private:
	UKismetSystemLibrary* KismetObjectChecking;
	
	bool StopExplosion;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
