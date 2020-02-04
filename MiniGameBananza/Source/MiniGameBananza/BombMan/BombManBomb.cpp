// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManBomb.h"
#include "Core/Public/Misc/AssertionMacros.h"
#include "Math/UnrealMathVectorCommon.h"

// Sets default values
ABombManBomb::ABombManBomb()
	: IsArmed(false), CountdownModifier(1.0f), TimeUntilDetonation(StartingDetonationTime), GrowthProgress(0.0f)
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

	HandleExplode(DeltaTime);

	HandleGrow(DeltaTime);
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

void ABombManBomb::HandleExplode(float DeltaTime)
{
	if (IsArmed)
	{
		TimeUntilDetonation -= DeltaTime * CountdownModifier;
		if (TimeUntilDetonation <= 0.0f)
		{
			BombDetonationEventHandler.ExecuteIfBound(this);

			Destroy();
		}
	}
}

void ABombManBomb::HandleGrow(float DeltaTime)
{
	if (GrowthProgress <= 1.0f)
	{
		GrowthProgress += DeltaTime * GrowthTime;

		GrowthProgress = FMath::Clamp<float>(GrowthProgress, 0, 1);

		SetActorScale3D(FMath::Lerp(MinimumScale, MaximumScale, GrowthProgress));
	}
}
