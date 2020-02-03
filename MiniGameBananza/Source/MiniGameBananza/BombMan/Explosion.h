// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Explosion.generated.h"

UCLASS()
class MINIGAMEBANANZA_API AExplosion : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, category = "Box")
	UBoxComponent* BoxCollision;
	
public:	
	// Sets default values for this actor's properties
	AExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
