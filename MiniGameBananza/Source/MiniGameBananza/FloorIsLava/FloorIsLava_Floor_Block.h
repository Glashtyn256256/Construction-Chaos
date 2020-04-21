// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "FloorIsLava_Floor_Block.generated.h"

UCLASS()
class MINIGAMEBANANZA_API AFloorIsLava_Floor_Block : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorIsLava_Floor_Block();

	virtual void DestroyObject();
	virtual void TogglePhysicsSimulation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
	
	int test = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	//virtual void SetSimulatePhysics();

};
