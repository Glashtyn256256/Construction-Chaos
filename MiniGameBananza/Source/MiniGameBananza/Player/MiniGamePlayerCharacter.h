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

	virtual void HandleRespawnProtection(float DeltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Ragdoll(FVector force = FVector::ZeroVector);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual FVector GetAnimVelocity() const;

	UFUNCTION(BlueprintCallable)
	virtual bool CanDie() const;

	UFUNCTION(BlueprintCallable)
	virtual bool HasRespawnProtection() const;

	UFUNCTION(BlueprintCallable)
	void SetVictory(bool bVictory);
	UFUNCTION(BlueprintCallable)
	void SetDeath(bool bDeath);
	UFUNCTION(BlueprintCallable)
	void SetJump(bool bJump);
	UFUNCTION(BlueprintCallable)
	void SetRespawn(bool bRespawn);
	UFUNCTION(BlueprintCallable)
	void SetDefeat(bool bDefeat);
	UFUNCTION(BlueprintCallable)
	bool GetVictory() const;
	UFUNCTION(BlueprintCallable)
	bool GetDeath() const;
	UFUNCTION(BlueprintCallable)
	bool GetJump() const;
	UFUNCTION(BlueprintCallable)
	bool GetRespawn() const;
	UFUNCTION(BlueprintCallable)
	bool GetDefeat() const;

private:
	void Interact();
	void Jump();

public:
	UPROPERTY(EditDefaultsOnly)
	float PlayerSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Respawn Protection")
	float MaxRespawnProtectionTime = 3.0f;

	UPROPERTY(EditDefaultsOnly)
	UMaterial* OpacityMaskedMaterial;
	UMaterial* DefaultMaterial;

protected:
	float InputForward;
	float InputRight;
	float RespawnProtectionTimer;

	bool bDeath;
	bool bJump;
	bool bVictory;
	bool bRespawn;
	bool bIsRagdoll;
	bool bHasRecentlyRespawned;
	bool bDefeat;
};
