// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBombManCollision.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIBombManCollision : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MINIGAMEBANANZA_API IIBombManCollision
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool IsPlayerCollide() const = 0;
	virtual void SetPlayerCollide(bool _bPlayerCollide) = 0;
	virtual bool CanBeDestroyed() const = 0;
	virtual void SetCanBeDestroyed(bool _bCanBeDestroyed) = 0;
};
