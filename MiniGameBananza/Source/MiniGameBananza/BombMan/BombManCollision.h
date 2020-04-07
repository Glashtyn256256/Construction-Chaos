// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "IBombManCollision.h"
#include "BombManCollision.generated.h"

class ABombManPlayerCharacter;

UCLASS()
class MINIGAMEBANANZA_API ABombManCollision : public AActor, public IIBombManCollision
{
	GENERATED_BODY()
	
public:	
	ABombManCollision();

	virtual bool IsPlayerCollide() const;
	virtual void SetPlayerCollide(bool _bPlayerCollide);
	virtual bool CanBeDestroyed() const;
	virtual void SetCanBeDestroyed(bool _bCanBeDestroyed);
	virtual void OnPlayerCollision(ABombManPlayerCharacter* Character);

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	bool bPlayerCollide = true;

	UPROPERTY(EditDefaultsOnly)
	bool bCanBeDestroyed = false;

};
