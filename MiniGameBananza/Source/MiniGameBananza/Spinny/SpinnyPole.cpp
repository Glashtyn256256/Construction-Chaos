// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyPole.h"

// Sets default values
ASpinnyPole::ASpinnyPole()
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
void ASpinnyPole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpinnyPole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FQuat RotationOffset = FQuat::MakeFromEuler(FVector::UpVector * CurrentRotationSpeed * DeltaTime);

	FQuat CurrentRotation = GetActorQuat();
	CurrentRotation *= RotationOffset;
	SetActorRotation(CurrentRotation);

}

