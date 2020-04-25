// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorIsLava_Floor_Block.h"
#include "Engine/Engine.h"

// Sets default values
AFloorIsLava_Floor_Block::AFloorIsLava_Floor_Block()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	if (MeshComponent)
	{
		MeshComponent->AttachTo(RootComponent);
	}

}

// Called when the game starts or when spawned
void AFloorIsLava_Floor_Block::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorIsLava_Floor_Block::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (test > 1000) {
		TogglePhysicsSimulation();
	}
	++test;
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Yellow, FString::FromInt(test));*/
}

void AFloorIsLava_Floor_Block::TogglePhysicsSimulation()
{
	MeshComponent->SetSimulatePhysics(true);
}

void AFloorIsLava_Floor_Block::DestroyObject() 
{
	this->ConditionalBeginDestroy();
}