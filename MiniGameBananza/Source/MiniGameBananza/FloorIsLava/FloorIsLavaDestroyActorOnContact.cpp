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

	BoxParameters = FVector(3000.0f, 3000.0f, 50.0f);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(RootComponent);
	}

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	if (BoxComponent) 
	{
		BoxComponent->InitBoxExtent(BoxParameters);
		BoxComponent->SetCollisionProfileName("Trigger");
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this,
			&AFloorIsLavaDestroyActorOnContact::OnOverlapBegin);
		RootComponent = BoxComponent;
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