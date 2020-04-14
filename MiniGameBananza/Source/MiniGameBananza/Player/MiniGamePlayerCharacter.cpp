// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayerCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

// Sets default values
AMiniGamePlayerCharacter::AMiniGamePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMiniGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void AMiniGamePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind action mappings
	PlayerInputComponent->BindAction("PlayerInteract", EInputEvent::IE_Pressed, this, &AMiniGamePlayerCharacter::Interact);
	PlayerInputComponent->BindAction("PlayerJump", EInputEvent::IE_Pressed, this, &AMiniGamePlayerCharacter::Jump);

	// Bind axis mappings to movement functions
	PlayerInputComponent->BindAxis("PlayerForward", this, &AMiniGamePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("PlayerRight", this, &AMiniGamePlayerCharacter::MoveRight);
}

// Called every frame
void AMiniGamePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// This is bound to the PlayerInputComponent
void AMiniGamePlayerCharacter::Interact()
{
	// Virtual function call
	OnInteract();
}

// This is bound to the PlayerInputComponent
void AMiniGamePlayerCharacter::Jump()
{
	// Virtual function call
	OnJump();
}

void AMiniGamePlayerCharacter::Ragdoll()
{

}

void AMiniGamePlayerCharacter::OnInteract()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("APlayerCharacter::OnInteract")));
}

void AMiniGamePlayerCharacter::OnJump()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("APlayerCharacter::OnJump")));
}

void AMiniGamePlayerCharacter::MoveForward(float Value)
{
	InputForward = Value;
	//AddMovementInput(GetActorForwardVector() * Value * playerSpeed);

	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	0.1f,
	//	FColor::Cyan,
	//	FString::Printf(TEXT("%f"), Value));
}

void AMiniGamePlayerCharacter::MoveRight(float Value)
{
	InputRight = Value;
	//AddMovementInput(GetActorRightVector() * Value * playerSpeed);

	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	0.1f,
	//	FColor::Green,
	//	FString::Printf(TEXT("%f"), Value));
}

FVector AMiniGamePlayerCharacter::GetAnimVelocity() const
{
	return FVector::ZeroVector;
}

