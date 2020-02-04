// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManBomb.h"
#include "Core/Public/Misc/AssertionMacros.h"

#include "Math/UnrealMathVectorCommon.h"
#include "Engine/Engine.h"

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

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	if (SphereComponent)
	{
		SphereComponent->AttachTo(RootComponent);
		SphereComponent->SetSphereRadius(50.0f);
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABombManBomb::OnBeginOverlap);
		SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ABombManBomb::OnEndOverlap);
	}

}

// Called when the game starts or when spawned
void ABombManBomb::BeginPlay()
{
	Super::BeginPlay();

	if (SphereComponent)
	{
		SphereComponent->SetWorldLocation(GetActorLocation());
	}
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
void ABombManBomb::OnBeginOverlap(UPrimitiveComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ABombManBomb::OnEndOverlap(UPrimitiveComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("End")));

	if (!SphereComponent || bStartShrinking) return;

	TArray<UPrimitiveComponent*> overlapping;
	SphereComponent->GetOverlappingComponents(overlapping);
	if (overlapping.Num() == 0)
	{
		bStartShrinking = true;
	}

}
