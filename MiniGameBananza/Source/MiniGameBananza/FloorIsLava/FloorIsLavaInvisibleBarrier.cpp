// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorIsLavaInvisibleBarrier.h"

// Sets default values
AFloorIsLavaInvisibleBarrier::AFloorIsLavaInvisibleBarrier()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	if (BoxComponent)
	{
		RootComponent = BoxComponent;
	}

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(RootComponent);
	}

	
}

// Called when the game starts or when spawned
void AFloorIsLavaInvisibleBarrier::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFloorIsLavaInvisibleBarrier::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

