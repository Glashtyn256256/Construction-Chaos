// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MiniGamePlayerCharacter.generated.h"

UCLASS()
class MINIGAMEBANANZA_API AMiniGamePlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMiniGamePlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		virtual void OnInteract();

	UFUNCTION()
		virtual void OnJump();

	UFUNCTION()
		virtual void MoveForward(float value);

	UFUNCTION()
		virtual void MoveRight(float Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Ragdoll();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void Interact();
	void Jump();

public:
	UPROPERTY(EditDefaultsOnly)
	float PlayerSpeed = 10.0f;

protected:
	float InputForward;
	float InputRight;

};
