// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"

#include "BombManBomb.generated.h"



#pragma region Delegate Decl

DECLARE_DELEGATE_OneParam(FOnBombDetonation, ABombManBomb *)

#pragma endregion

UCLASS()
class MINIGAMEBANANZA_API ABombManBomb : public AActor
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

	void SetCountdownModifier(float Value);

	void HandleExplode(float DeltaTime);

	void HandleGrow(float DeltaTime);

public:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;

	// How long it takes for the bomb to explode when armed
	UPROPERTY(EditDefaultsOnly)
	float StartingDetonationTime = 4.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Growth Animation")
	float GrowthTime = 1.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Growth Animation")
	FVector MaximumScale = FVector::OneVector;

	UPROPERTY(EditDefaultsOnly, Category = "Growth Animation")
	FVector MinimumScale = FVector(0.25f, 0.25f, 0.25f);

	// Delegate
	FOnBombDetonation BombDetonationEventHandler;

protected:


private:
	bool IsArmed;
	float TimeUntilDetonation;
	float CountdownModifier;
	float GrowthProgress;

};
