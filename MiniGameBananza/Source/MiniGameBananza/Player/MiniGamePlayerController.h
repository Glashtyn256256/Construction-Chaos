// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MiniGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API AMiniGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();
	
};
