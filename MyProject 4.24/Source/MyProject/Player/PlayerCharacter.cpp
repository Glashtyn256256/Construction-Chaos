// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "APlayerCharacterMovement.h"
#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComponenet = CreateDefaultSubobject<UAPlayerCharacterMovement>(TEXT("Player Movement Component"));
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAxis("PlayerForward",	MovementComponenet, MovementComponenet->MoveForward();
	InputComponent->BindAxis("PlayerRight",		MovementComponenet,  MovementComponenet->MoveRight);
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