// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManExplosion.h"

// Sets default values
ABombManExplosion::ABombManExplosion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	if (BoxComponent) {
		BoxComponent->AttachTo(RootComponent);
	}

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	if (ParticleSystem) {
		ParticleSystem->AttachTo(BoxComponent);
	}

}

// Called when the game starts or when spawned
void ABombManExplosion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABombManExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

