// Fill out your copyright notice in the Description page of Project Settings.

#include "BombManExplosion.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
ABombManExplosion::ABombManExplosion() : StopExplosion(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	if (Root) {
		RootComponent = Root;
	}

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
	
	//if (GetWorld() == NULL) {
	//	StartLocation.Set(10,10,10);
	//}
	//else {
	//	StartLocation.Set(40, 40, 40);
	//}
	
	StartLocation = GetActorLocation();
	EndLocation = GetActorLocation() + (GetActorForwardVector() * Length);
	//KismetObjectChecking->BoxTraceForObjects(this, StartLocation, EndLocation, );
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

