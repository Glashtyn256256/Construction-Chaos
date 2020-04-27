// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinnyPole.h"
#include "MiniGameBananza/Gamemode/SpinnyGamemode.h"
#include "MiniGameBananza/Player/SpinnyPlayerController.h"
#include "MiniGameBananza/Player/SpinnyPlayerCharacter.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASpinnyPole::ASpinnyPole() : PreviousRotationSpeed(CurrentRotationSpeed)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	if (MeshComponent)
	{
		MeshComponent->AttachTo(RootComponent);
		MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASpinnyPole::OnOverlapBegin);
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

	CurrentRotationSpeed += DeltaTime * RotationSpeedIncrementModifier;
}

void ASpinnyPole::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASpinnyPlayerCharacter* Character = Cast<ASpinnyPlayerCharacter>(OtherActor);
	if (Character)
	{
		FVector Force = SweepResult.ImpactNormal * PoleImpactForceModifier;

		if (Character->CanDie())
		{
			Character->Die(Force);
		}
		else if (Character->HasRespawnProtection())
		{
			Character->bPoleHasPassed = true;
		}
	}
}

