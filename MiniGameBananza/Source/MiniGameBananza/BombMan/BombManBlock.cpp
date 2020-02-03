// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManBlock.h"

// Sets default values
ABombManBlock::ABombManBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	if (MeshComponent)
	{
		MeshComponent->AttachTo(RootComponent);
	}
}

// Called when the game starts or when spawned
void ABombManBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABombManBlock::DestroyBlock()
{
	Destroy();
}

