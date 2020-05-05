// Fill out your copyright notice in the Description page of Project Settings.

#include "BombManExplosion.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "GameFramework/DamageType.h"
#include "Math/UnrealMathUtility.h"
#include "MiniGameBananza/Player/BombManPlayerController.h"
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
		SphereComponent->SetSphereRadius(10.0f);
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ABombManExplosion::OnBeginOverlap);
	}

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System Component"));
	if (ParticleSystem) {
		ParticleSystem->AttachTo(RootComponent);
	}

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	if (AudioComponent)
	{
		AudioComponent->AttachTo(RootComponent);
	}
}

// Called when the game starts or when spawned
void ABombManExplosion::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	if (AudioComponent)
	{
		USoundCue* sc = ExplosionSoundCues[FMath::RandRange(0, ExplosionSoundCues.Num() - 1)];
		AudioComponent->SetSound(sc);
		AudioComponent->Play();
	}
}

void ABombManExplosion::OnBeginOverlap(UPrimitiveComponent* Component, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABombManPlayerCharacter* bombVictim = Cast<ABombManPlayerCharacter>(OtherActor);
	if (bombVictim)
	{
		// Create a valid damage event
		const TSubclassOf<UDamageType> validDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent damageEvent(validDamageTypeClass);

		bombVictim->TakeDamage(1.0f, damageEvent, BombPlanter, this);
	}

	ABombManCollision* collision = Cast<ABombManCollision>(OtherActor);
	if (collision)
	{
		ABombManExplosion* explosion = Cast<ABombManExplosion>(collision);

		if (explosion) return;

		ABombManBomb* Bomb = Cast<ABombManBomb>(collision);

		if (Bomb)
		{
			Bomb->Explode();
			return;
		}

		if (collision->CanBeDestroyed())
		{
			collision->Destroy();
		}

		StopExplosion = true;
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

void ABombManExplosion::SetBombPlanter(ABombManPlayerController* _BombPlanter)
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

