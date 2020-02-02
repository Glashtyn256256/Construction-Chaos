// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	MovementComponent = CreateDefaultSubobject<UPlayerCharacterMovement>(TEXT("Movement Component"));

	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	if (OurVisibleComponent)
	{
		OurVisibleComponent->SetSimulatePhysics(false);
		OurVisibleComponent->SetupAttachment(RootComponent);
	}

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	if (BoxComponent)
	{
		BoxComponent->SetupAttachment(OurVisibleComponent);
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

}

void APlayerCharacter::MoveForward(float Value)
{
	MovementComponent->AddInputVector(FVector(10, 0, 0) * Value,true);

	//AddMovementInput(FVector(50, 0, 0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("%f"), Value));
}

void APlayerCharacter::MoveRight(float Value)
{
	MovementComponent->AddInputVector(FVector(0, 10, 0) * Value, true);

	//AddMovementInput(FVector(0, 50, 0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Green,
		FString::Printf(TEXT("%f"), Value));
}

