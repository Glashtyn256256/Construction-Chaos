// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorIsLava_Block_Manager.h"
#include "EngineUtils.h"
#include "FloorIsLava_Floor_Block.h"
#include "Engine/Engine.h"

// Sets default values
AFloorIsLava_Block_Manager::AFloorIsLava_Block_Manager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UWorld* world = GetWorld();

	/*for (TActorIterator<AFloorIsLava_Floor_Block> It(world, AFloorIsLava_Floor_Block::StaticClass()); It; It++)
	{
		AFloorIsLava_Floor_Block* blockActor = *It;
		if (blockActor != NULL)
			FloorBlocks.Add(blockActor);
	}*/

	for (TObjectIterator<AFloorIsLava_Floor_Block> Itr; Itr; ++Itr)
	{
		if (Itr->IsA(AFloorIsLava_Floor_Block::StaticClass()))
		{
			AFloorIsLava_Floor_Block* block = *Itr;
			if (block)
			{
				FloorBlocks.Add(block);
			}
		}
	}
}

// Called when the game starts or when spawned
void AFloorIsLava_Block_Manager::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFloorIsLava_Block_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (time > maxTime)
	{
		SelectRandomCube();
		time = 0;
	}
	time += DeltaTime;
	//GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::FromInt(FloorBlocks.Num() - 1));
}

void AFloorIsLava_Block_Manager::SelectRandomCube()
{
	int32 blockCount = FloorBlocks.Num();
	if (blockCount <= 0)
		return;

	int32 randomIndexPosition = FMath::RandRange(0, blockCount - 1);

	AFloorIsLava_Floor_Block* floorBlock = FloorBlocks[randomIndexPosition];
	if (floorBlock)
	{
		FloorBlocks.Remove(floorBlock);
		floorBlock->TogglePhysicsSimulation();
		//floorBlock->DestroyObject();
	}
}