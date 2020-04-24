// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorIsLavaDestroyActorOnContact.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AFloorIsLavaDestroyActorOnContact::AFloorIsLavaDestroyActorOnContact()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereRadius = 2000.0f;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	if (SphereComponent)
	{
		SphereComponent->InitSphereRadius(SphereRadius);
		SphereComponent->SetCollisionProfileName("Trigger");
		RootComponent = SphereComponent;
	}

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	if (MeshComponent)
	{
		MeshComponent->SetupAttachment(RootComponent);
	}

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,
		&AFloorIsLavaDestroyActorOnContact::OnOverlapBegin);

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
		OtherActor->Destroy();
	}
}