// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BombManBomb.generated.h"

UCLASS()
class MINIGAMEBANANZA_API ABombManBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABombManBomb(bool Armed = true);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ArmBomb();
	void DefuseBomb();
	void ResetBomb();

	void SetCountdownModifier(float Value);

	void Explode();

public:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	// How long it takes for the bomb to explode when armed
	UPROPERTY(EditDefaultsOnly)
	float DetonationTime = 4.5f;

protected:


private:
	bool IsArmed;
	float TimeUntilDetonation;
	float CountdownModifier;

};
