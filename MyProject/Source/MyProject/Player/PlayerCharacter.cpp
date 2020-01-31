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

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("PlayerForward",	this, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("PlayerRight",		this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(FVector(50,0,0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("%f"), Value));
}

void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(FVector(0, 50, 0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Green,
		FString::Printf(TEXT("%f"), Value));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}