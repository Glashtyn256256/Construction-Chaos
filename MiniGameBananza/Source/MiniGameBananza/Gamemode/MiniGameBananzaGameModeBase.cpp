// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.


#include "MiniGameBananzaGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void AMiniGameBananzaGameModeBase::InitGame(const FString & MapName, const FString & Options, FString & ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	const UWorld* world = GetWorld();
	if (world)
	{
		TArray<APlayerController*> playerControllers;
		for (int i = 0; i <= PlayerCount; ++i)
		{
			playerControllers.Add(UGameplayStatics::CreatePlayer(world, i));
		}

		TArray<AActor*> foundActors;
		UGameplayStatics::GetAllActorsOfClass(world, ACameraActor::StaticClass(), foundActors);

		if (foundActors.Num() > 0)
		{
			CameraActor = foundActors[0];
		}


		for (AActor* actor : foundActors)
		{
			TArray< UActorComponent*> validComponents = actor->GetComponentsByTag(UActorComponent::StaticClass(), TEXT("MainCamera"));
			if (validComponents.Num() > 0)
			{
				CameraActor = actor;
			}
		}

		for (APlayerController* playerController : playerControllers)
		{
			if (playerController && CameraActor)
			{
				playerController->SetViewTargetWithBlend(CameraActor);
			}
		}
	}
}
