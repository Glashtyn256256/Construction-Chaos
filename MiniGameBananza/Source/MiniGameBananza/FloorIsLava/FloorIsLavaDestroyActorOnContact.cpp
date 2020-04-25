// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorIsLavaDestroyActorOnContact.h"
#include "Components/PrimitiveComponent.h"
#include "MiniGameBananza/Player/FloorIsLavaPlayerCharacter.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/DamageType.h"

// Sets default values
AFloorIsLavaDestroyActorOnContact::AFloorIsLavaDestroyActorOnContact()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 2000.0f;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(RootComponent);
	}

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	if (SphereComponent)
	{
		SphereComponent->InitSphereRadius(SphereRadius);
		SphereComponent->SetCollisionProfileName("Trigger");
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this,
			&AFloorIsLavaDestroyActorOnContact::OnOverlapBegin);
		RootComponent = SphereComponent;
	}
}

// Called when the game starts or when spawned
void AFloorIsLavaDestroyActorOnContact::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFloorIsLavaDestroyActorOnContact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, false, -1, 0, 1);
}

void AFloorIsLavaDestroyActorOnContact::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AFloorIsLavaPlayerCharacter* victim = Cast<AFloorIsLavaPlayerCharacter>(OtherActor);
		if (victim)
		{
			// Create a valid damage event
			const TSubclassOf<UDamageType> validDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
			FDamageEvent damageEvent(validDamageTypeClass);

			victim->TakeDamage(1.0f, damageEvent, victim->Controller, this);
		}
		else
		{
			OtherActor->Destroy();
		}
	}
}