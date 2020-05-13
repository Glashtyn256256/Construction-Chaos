// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniGamePlayerCharacter.h"

#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Engine/Engine.h"
#include "Materials/Material.h"


// Sets default values
AMiniGamePlayerCharacter::AMiniGamePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USkeletalMeshComponent* MeshLocal = GetMesh();
	if (MeshLocal && MeshLocal->GetMaterial(0))
	{
		DefaultMaterial = MeshLocal->GetMaterial(0)->GetMaterial();
	}
}

// Called when the game starts or when spawned
void AMiniGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	bHasRecentlyRespawned = true;
	RespawnProtectionTimer = MaxRespawnProtectionTime;
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

	HandleRespawnProtection(DeltaTime);
}

void AMiniGamePlayerCharacter::Ragdoll(FVector force)
{
	USkeletalMeshComponent* MeshLocal = GetMesh();
	if (MeshLocal)
	{
		GetCharacterMovement()->DisableMovement();
		MeshLocal->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		MeshLocal->SetAllBodiesSimulatePhysics(true);
		MeshLocal->AddImpulseToAllBodiesBelow(force, EName::NAME_None, true);

		bIsRagdoll = true;
	}
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

void AMiniGamePlayerCharacter::OnInteract()
{
	/*GEngine->AddOnScreenDebugMessage(
		-1,
		0.1f,
		FColor::Cyan,
		FString::Printf(TEXT("APlayerCharacter::OnInteract")));*/
}

void AMiniGamePlayerCharacter::OnJump()
{
	//GEngine->AddOnScreenDebugMessage(
	//	-1,
	//	0.1f,
	//	FColor::Cyan,
	//	FString::Printf(TEXT("APlayerCharacter::OnJump")));
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

void AMiniGamePlayerCharacter::HandleRespawnProtection(float DeltaTime)
{
	if (bHasRecentlyRespawned)
	{
		RespawnProtectionTimer -= DeltaTime;
		if (RespawnProtectionTimer <= 0)
		{
			bHasRecentlyRespawned = false;
		}
	}

	if (HasRespawnProtection())
	{
		USkeletalMeshComponent* MeshLocal = GetMesh();
		if (MeshLocal)
		{
			MeshLocal->SetMaterial(0, OpacityMaskedMaterial);
		}
	}
	else
	{
		USkeletalMeshComponent* MeshLocal = GetMesh();
		if (MeshLocal)
		{
			MeshLocal->SetMaterial(0, DefaultMaterial);
		}
	}
}

void AMiniGamePlayerCharacter::RemoveRespawnProtection()
{
	bHasRecentlyRespawned = false;
	RespawnProtectionTimer = 0;
}

FVector AMiniGamePlayerCharacter::GetAnimVelocity() const
{
	return FVector::ZeroVector;
}

bool AMiniGamePlayerCharacter::CanDie() const
{
	return !HasRespawnProtection() && !GetDeath();
}

bool AMiniGamePlayerCharacter::HasRespawnProtection() const
{
	return bHasRecentlyRespawned;
}

void AMiniGamePlayerCharacter::SetVictory(bool _bVictory)
{
	this->bVictory = _bVictory;
}

void AMiniGamePlayerCharacter::SetDeath(bool _bDeath)
{
	this->bDeath = _bDeath;
}

void AMiniGamePlayerCharacter::SetJump(bool _bJump)
{
	this->bJump = _bJump;
}

void AMiniGamePlayerCharacter::SetRespawn(bool _bRespawn)
{
	this->bRespawn = _bRespawn;
}

void AMiniGamePlayerCharacter::SetDefeat(bool _bDefeat)
{
	this->bDefeat = _bDefeat;
}

void AMiniGamePlayerCharacter::SetVictory2(bool _bVictory2)
{
	this->bVictory2 = _bVictory2;
}

void AMiniGamePlayerCharacter::SetExcited(bool _bExcited)
{
	this->bExcited = _bExcited;
}

bool AMiniGamePlayerCharacter::GetVictory() const
{
	return bVictory;
}

bool AMiniGamePlayerCharacter::GetDeath() const
{
	return bDeath;
}

bool AMiniGamePlayerCharacter::GetJump() const
{
	return bJump;
}

bool AMiniGamePlayerCharacter::GetRespawn() const
{
	return bRespawn;
}

bool AMiniGamePlayerCharacter::GetDefeat() const
{
	return bDefeat;
}

bool AMiniGamePlayerCharacter::GetExcited() const
{
	return bExcited;
}

bool AMiniGamePlayerCharacter::GetVictory2() const
{
	return bVictory2;
}

