// Fill out your copyright notice in the Description page of Project Settings.


#include "BombManCollision.h"

// Sets default values
ABombManCollision::ABombManCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	if (MeshComponent)
	{
		MeshComponent->AttachTo(RootComponent);
	}
}

#pragma region Getters/Setters

bool ABombManCollision::IsPlayerCollide() const
{
	return bPlayerCollide;
}

void ABombManCollision::SetPlayerCollide(bool _bPlayerCollide)
{
	this->bPlayerCollide = _bPlayerCollide;
}

bool ABombManCollision::CanBeDestroyed() const
{
	return bCanBeDestroyed;
}

void ABombManCollision::SetCanBeDestroyed(bool _bCanBeDestroyed)
{
	this->bCanBeDestroyed = _bCanBeDestroyed;
}

#pragma endregion

