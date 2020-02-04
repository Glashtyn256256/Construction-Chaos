// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManBomb.h"
#include "Core/Public/Misc/AssertionMacros.h"

// Sets default values
ABombManBomb::ABombManBomb()
	: IsArmed(false), CountdownModifier(1.0f), TimeUntilDetonation(StartingDetonationTime)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
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
		TimeUntilDetonation -= DeltaTime * CountdownModifier;
		if (TimeUntilDetonation <= 0.0f)
		{
			Explode();
		}
	}
}

void ABombManBomb::SetCountdownModifier(float Value)
{
	if (ensure(Value > 0 && "Modifier value should never be below 0"))
	{
		CountdownModifier = Value;
	}
}

void ABombManBomb::Arm()
{
	IsArmed = true;
}

void ABombManBomb::Defuse()
{
	IsArmed = false;
}

void ABombManBomb::Reset()
{
	TimeUntilDetonation = StartingDetonationTime;
}

void ABombManBomb::Explode()
{
	BombDetonationEventHandler.ExecuteIfBound(this);

	Destroy();
}
