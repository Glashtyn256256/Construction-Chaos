// Fill out your copyright notice in the Description page of Project Settings.

#include "BombManExplosion.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "MiniGameBananza/Player/BombManPlayerCharacter.h"
#include "BombManBomb.h"

// Sets default values
ABombManExplosion::ABombManExplosion() 
	: StopExplosion(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	if (Root) {
		RootComponent = Root;
	}

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	if (SphereComponent) {
		SphereComponent->AttachTo(RootComponent);
		SphereComponent->SetSphereRadius(25.0f);
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABombManExplosion::OnBeginOverlap);
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

void ABombManExplosion::OnBeginOverlap(UPrimitiveComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABombManPlayerCharacter* bombVictim = Cast<ABombManPlayerCharacter>(OtherActor);
	if (bombVictim)
	{
		if (BombPlanter && BombPlanter != bombVictim)
		{
			// BombPlanter killed bombVictim
			bombVictim->HitByBomb(false);
			BombPlanter->EnemyPlayerHitByMyBomb();
		}
		else if (BombPlanter)
		{
			// BombPlanter committed suicide
			BombPlanter->HitByBomb(true);
		}
	}

	ABombManBlock* block = Cast<ABombManBlock>(OtherActor);
	if (block)
	{
		if (block->CanBeDestroyed())
		{
			block->DestroyBlock();
			StopExplosion = true;
		}
		else
		{
			StopExplosion = true;
		}
	}
}

// Called every frame
void ABombManExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (StopExplosion == false)
	{
		HandleExplosion(DeltaTime);
	}
	else
	{
		HandleFadeOut();
	}
}

void ABombManExplosion::SetBombPlanter(ABombManPlayerCharacter* _BombPlanter)
{
	BombPlanter = _BombPlanter;
}

void ABombManExplosion::HandleExplosion(float DeltaTime)
{
	FVector NewLocation = GetActorForwardVector() * (Speed * DeltaTime);
	AddActorWorldOffset(NewLocation, true);
	FVector VectorLength = StartLocation - GetActorLocation();

	if (VectorLength.Size() >= Length)
	{
		StopExplosion = true;
	}
}

void ABombManExplosion::HandleFadeOut()
{
	if (ParticleSystem->IsActive())
	{
		ParticleSystem->Deactivate();
	}

	if (ParticleSystem->GetNumActiveParticles() == 0)
	{
		Destroy();
	}
}
