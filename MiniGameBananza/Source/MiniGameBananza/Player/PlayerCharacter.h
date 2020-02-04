// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class MINIGAMEBANANZA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:


private:
	UFUNCTION()
	virtual void MoveForward(float value);

	UFUNCTION()
	virtual void MoveRight(float Value);

public:
	UPROPERTY(EditDefaultsOnly)
	float PlayerSpeed = 10.0f;

};
