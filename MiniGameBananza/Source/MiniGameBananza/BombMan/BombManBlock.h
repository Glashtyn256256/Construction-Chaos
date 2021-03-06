// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BombManCollision.h"
#include "BombManBlock.generated.h"

UCLASS()
class MINIGAMEBANANZA_API ABombManBlock : public ABombManCollision
{
	GENERATED_BODY()
	
public:	

	ABombManBlock();

protected:

	virtual void BeginPlay() override;


};
