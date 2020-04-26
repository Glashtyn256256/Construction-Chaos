// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorIsLavaPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "MiniGameBananza/Player/FloorIsLavaPlayerController.h"
#include "MiniGameBananza/Gamemode/FloorIsLavaGamemode.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

AFloorIsLavaPlayerCharacter::AFloorIsLavaPlayerCharacter() 
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereRadius = 30.0f;
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collider"));
	if (SphereCollider)
	{
		SphereCollider->InitSphereRadius(SphereRadius);
		SphereCollider->SetCollisionProfileName("Trigger");
		SphereCollider->OnComponentBeginOverlap.AddDynamic(this,
			&AFloorIsLavaPlayerCharacter::OnOverlapBegin);
		SphereCollider->SetupAttachment(RootComponent);
	}
}
	// Called every frame
void AFloorIsLavaPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

//	PreventCharacterStandingStill();
	Velocity = (GetActorForwardVector() * InputForward) + (GetActorRightVector() * InputRight);
	Velocity *= MovementSpeed * DeltaTime;

	AddMovementInput(Velocity, 1.0f);

	USkeletalMeshComponent* MeshComponent = GetMesh();
	if (MeshComponent && Velocity.Size() >= 0.1f)
	{
		FRotator Rotation = FRotator(Velocity.Rotation());
		Rotation.Add(0.0f, 270.0f, 0.0f);

		FRotator CurrentRotation = MeshComponent->GetRelativeRotation();

		FQuat SmoothRotation = FQuat::Slerp(CurrentRotation.Quaternion(), Rotation.Quaternion(), DeltaTime * 20.0f);

		MeshComponent->SetRelativeRotation(SmoothRotation.Rotator());
	}
}

float AFloorIsLavaPlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
		AFloorIsLavaPlayerController* LavaController = Cast<AFloorIsLavaPlayerController>(Controller);
		if (LavaController)
		{
			Destroy();
			LavaController->StartRespawnProcess();
			AMiniGameBananzaGameModeBase* gamemode = Cast<AMiniGameBananzaGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
			if (gamemode)
			{
				LavaController->SetViewTargetWithBlend(gamemode->CameraActor);
			}
		}

		return Damage;
}

FVector AFloorIsLavaPlayerCharacter::GetAnimVelocity() const
{
	return Velocity * 10.0f;
}

void AFloorIsLavaPlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		AFloorIsLavaPlayerCharacter* victim = Cast<AFloorIsLavaPlayerCharacter>(OtherActor);
		if (victim)
		{
		}
	}
}

//void AFloorIsLavaPlayerCharacter::PreventCharacterStandingStill() 
//{
//	FHitResult OutHit;
//	FVector Start = SphereCollider->GetComponentLocation();
//
//	FVector ForwardVector = SphereCollider->GetForwardVector() + FVector(0, 0, -90);
//	FVector End = ((ForwardVector * 100.0f) + Start);
//	FCollisionQueryParams CollisionParams;
//	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, true, -1, 0, 5.0f);
//
//	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 20, FColor::Purple, false, -1, 0, 1);
//
//	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_Visibility, CollisionParams);
//
//	if (isHit)
//	{
//
//		if (OutHit.bBlockingHit)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, OutHit.GetActor()->GetName());
//		}
//	}
}