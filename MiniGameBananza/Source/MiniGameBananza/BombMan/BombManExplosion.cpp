// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/World.h"
#include "Engine/Engine.h"
#include "BombManExplosion.h"

// Sets default values
ABombManExplosion::ABombManExplosion() : StopExplosion(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	if (BoxComponent) {
		BoxComponent->AttachTo(RootComponent);
	}
	
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	if (ParticleSystem) {
		ParticleSystem->AttachTo(RootComponent);
	}
}

// Called when the game starts or when spawned
void ABombManExplosion::BeginPlay()
{
	
	Super::BeginPlay();
	StartLocation = GetActorLocation();	
}

// Called every frame
void ABombManExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StopExplosion == false)
	{
		FVector NewLocation = GetActorForwardVector() * (Speed * DeltaTime);
		AddActorWorldOffset(NewLocation, true);
		FVector VectorLength = StartLocation - GetActorLocation();

		if (VectorLength.Size() >= Length)
		{
			StopExplosion = true;
		}
	}
}

