// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "SpinnyPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class MINIGAMEBANANZA_API ASpinnyPlayerCharacter : public AMiniGamePlayerCharacter
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Die(FVector force);
protected:

	virtual void OnJump() override;

private:
	float jumpAnimTime;
};
