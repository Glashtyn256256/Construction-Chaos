// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManBomb.h"

// Sets default values
ABombManBomb::ABombManBomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (StaticMeshComponent)
	{
		StaticMeshComponent->AttachTo(RootComponent);
	}

}

// Called when the game starts or when spawned
void ABombManBomb::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABombManBomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsArmed)
	{
		TimeUntilDetonation -= DeltaTime;
	}
}

void ABombManBomb::ArmBomb()
{
	IsArmed = true;
}

void ABombManBomb::DefuseBomb()
{
	IsArmed = false;
}

void ABombManBomb::ResetBomb()
{
	TimeUntilDetonation = DetonationTime;
}
