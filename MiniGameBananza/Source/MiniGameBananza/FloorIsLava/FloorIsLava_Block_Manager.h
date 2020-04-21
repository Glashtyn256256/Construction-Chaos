// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorIsLava_Floor_Block.h"
#include "FloorIsLava_Block_Manager.generated.h"

UCLASS()
class MINIGAMEBANANZA_API AFloorIsLava_Block_Manager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorIsLava_Block_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SelectRandomCube();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	int test = 0;

private:

	UPROPERTY(EditDefaultsOnly)
	TArray<AFloorIsLava_Floor_Block*> FloorBlocks;
};
