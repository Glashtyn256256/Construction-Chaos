// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
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

	// Bind action mappings
	PlayerInputComponent->BindAction("PlayerInteract", EInputEvent::IE_Pressed, this, &APlayerCharacter::Interact);

	// Bind axis mappings to movement functions
	PlayerInputComponent->BindAxis("PlayerForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerRight", this, &APlayerCharacter::MoveRight);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// This is bound to the PlayerInputComponent
void APlayerCharacter::Interact()
{
	// Virtual function call
	OnInteract();
}

void APlayerCharacter::OnInteract()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("APlayerCharacter::OnInteract")));
}

void APlayerCharacter::MoveForward(float Value)
{
	InputForward = Value;
	//AddMovementInput(GetActorForwardVector() * Value * playerSpeed);

	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	0.1f,
	//	FColor::Cyan,
	//	FString::Printf(TEXT("%f"), Value));
}

void APlayerCharacter::MoveRight(float Value)
{
	InputRight = Value;
	//AddMovementInput(GetActorRightVector() * Value * playerSpeed);

	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	0.1f,
	//	FColor::Green,
	//	FString::Printf(TEXT("%f"), Value));
}

