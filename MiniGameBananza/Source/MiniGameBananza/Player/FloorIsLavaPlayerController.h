// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGamePlayerController.h"
#include "FloorIsLavaPlayerCharacter.h"
#include "FloorIsLavaPlayerController.generated.h"


UCLASS()
class MINIGAMEBANANZA_API AFloorIsLavaPlayerController : public AMiniGamePlayerController
{
	GENERATED_BODY()
	
#pragma region Functions
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
#pragma endregion

#pragma region Variables
public:


#pragma endregion

};
