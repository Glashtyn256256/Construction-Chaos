// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayerCharacterMovement.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values for this component's properties
UAPlayerCharacterMovement::UAPlayerCharacterMovement()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UAPlayerCharacterMovement::MoveForward(float Value, APlayerCharacter* character)
{
	character->AddMovementInput(FVector(50, 0, 0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("%f"), Value));
}

 void UAPlayerCharacterMovement::MoveRight(float Value, APlayerCharacter* character)
{
	character->AddMovementInput(FVector(0, 50, 0), Value);
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Green,
		FString::Printf(TEXT("%f"), Value));
}

// Called when the game starts
void UAPlayerCharacterMovement::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAPlayerCharacterMovement::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
