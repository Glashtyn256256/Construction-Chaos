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
	ASpinnyPlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void Die(FVector force);

	virtual void Ragdoll(FVector force = FVector::ZeroVector) override;

	virtual void Destroyed() override;
protected:

	virtual void OnJump() override;

	virtual void HandleRespawnProtection(float DeltaTime) override;

public:
	UPROPERTY(EditDefaultsOnly, Category = "Respawn Protection")
		float MaxRespawnProtectionTime = 5.0f;

private:
	float RespawnProtectionTimer;

};
