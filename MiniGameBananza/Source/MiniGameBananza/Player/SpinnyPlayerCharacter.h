// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"
#include "Components/AudioComponent.h"
#include "Engine/Classes/Sound/SoundCue.h"
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

	virtual void Destroyed() override;
	
	virtual bool HasRespawnProtection() const override;

	virtual void RemoveRespawnProtection() override;
protected:

	virtual void OnJump() override;

	virtual void HandleRespawnProtection(float DeltaTime) override;

private:

	bool IsCollidingWithPole() const;

public:
	UPROPERTY(EditDefaultsOnly)
	USoundCue* scHit;

	bool bPoleHasPassed; // Used to check if the pole has passed through the player during respawn protection

private:
	UAudioComponent* AudioComponent;

	float deadTime;
	float jumpAnimTime;
	
};
