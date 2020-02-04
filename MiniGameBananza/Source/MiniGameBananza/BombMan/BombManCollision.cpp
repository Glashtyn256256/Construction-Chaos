// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManCollision.h"

// Sets default values
ABombManCollision::ABombManCollision()
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
void ABombManCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombManCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

