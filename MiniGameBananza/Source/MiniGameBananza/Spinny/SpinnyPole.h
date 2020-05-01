// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpinnyPole.generated.h"

UCLASS()
class MINIGAMEBANANZA_API ASpinnyPole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinnyPole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	float RotationSpeedIncrementModifier = 1.5f;

	UPROPERTY(EditDefaultsOnly)
	float PoleImpactForceModifier = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float CurrentRotationSpeed = 20.0f;

	float PreviousRotationSpeed;

};
