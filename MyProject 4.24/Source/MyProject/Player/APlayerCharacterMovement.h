// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/InputComponent.h"
#include "PlayerCharacter.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "APlayerCharacterMovement.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UAPlayerCharacterMovement : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAPlayerCharacterMovement();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

//private:
	UFUNCTION()
		void MoveForward(float value, APlayerCharacter* character);

	UFUNCTION()
		void MoveRight(float Value, APlayerCharacter* character);
};
