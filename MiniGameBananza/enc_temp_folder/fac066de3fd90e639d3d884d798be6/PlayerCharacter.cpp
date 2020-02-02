// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter() : playerForward(0.0f),playerRight(0.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	if (OurVisibleComponent)
	{
		OurVisibleComponent->SetSimulatePhysics(true);
		OurVisibleComponent->SetupAttachment(RootComponent);
		OurVisibleComponent->BodyInstance.bLockXRotation = true;
		OurVisibleComponent->BodyInstance.bLockYRotation = true;
		OurVisibleComponent->BodyInstance.bLockZRotation = true;
	}
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind axis mappings to movement functions
	PlayerInputComponent->BindAxis("PlayerForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerRight", this, &APlayerCharacter::MoveRight);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OurVisibleComponent) return;

	FVector forward = GetActorForwardVector() * playerForward;
	FVector right = GetActorRightVector() * playerRight;

	OurVisibleComponent->BodyInstance.SetLinearVelocity((forward + right) * playerSpeed, false);

}

void APlayerCharacter::MoveForward(float Value)
{
	playerForward = Value;

	//AddMovementInput(FVector(50, 0, 0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("%f"), Value));
}

void APlayerCharacter::MoveRight(float Value)
{
	playerRight = Value;

	//AddMovementInput(FVector(0, 50, 0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Green,
		FString::Printf(TEXT("%f"), Value));
}

