// Fill out your copyright notice in the Description page of Project Settings.


#include "WinGamemode.h"
#include "GameFramework/PlayerStart.h"
#include "MiniGameBananza/Utils/MiniGameBananzaGameInstance.h"
#include "MiniGameBananza/Player/MiniGamePlayerCharacter.h"

void AWinGamemode::BeginPlay()
{
	Super::BeginPlay();
}

void AWinGamemode::OnCharacterSpawned(AController* Controller, APawn* Pawn)
{
	UMiniGameBananzaGameInstance* GameInstance = Cast< UMiniGameBananzaGameInstance>(GetGameInstance());
	AMiniGamePlayerController* MiniController = Cast< AMiniGamePlayerController>(Controller);

	AMiniGamePlayerCharacter* Character = Cast<AMiniGamePlayerCharacter>(Pawn);
	if (Character && GameInstance && MiniController)
	{
		if (MiniController->GetLocalPlayer())
		{
			int id = MiniController->GetLocalPlayer()->GetControllerId();

			TArray<int> scoreOrders = GameInstance->GetPlayersIDInOrderBasedOnScore();

			int scorePosition = scoreOrders.Find(id);

			if (scoreOrders.Num() - 1 == scorePosition)
			{
				Character->SetDefeat(true);
			}
			else
			{
				Character->SetVictory(true);
			}
		}
	}
}

AActor* AWinGamemode::GetSpawnPoint(AMiniGamePlayerController* Controller)
{
	UMiniGameBananzaGameInstance* GameInstance = Cast< UMiniGameBananzaGameInstance>(GetGameInstance());

	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), foundActors);
	for (AActor* actor : foundActors)
	{
		if (actor)
		{
			if (actor->GetFName() == "FirstPlaceSpawn")
			{
				FirstPlaceSpawn = actor;
			}
			else if (actor->GetFName() == "SecondPlaceSpawn")
			{
				SecondPlaceSpawn = actor;
			}
			else if (actor->GetFName() == "ThirdPlaceSpawn")
			{
				ThirdPlaceSpawn = actor;
			}
			else if (actor->GetFName() == "FourthPlaceSpawn")
			{
				FourthPlaceSpawn = actor;
			}
		}
	}

	if (GameInstance)
	{
		if (Controller && Controller->GetLocalPlayer())
		{
			int id = Controller->GetLocalPlayer()->GetControllerId();

			int scorePosition = GameInstance->GetPlayersIDInOrderBasedOnScore().Find(id);
			switch (scorePosition)
			{
			case 0: return FirstPlaceSpawn;
			case 1: return SecondPlaceSpawn;
			case 2: return ThirdPlaceSpawn;
			case 3: return FourthPlaceSpawn;
			}
		}
	}

	return Super::GetSpawnPoint(Controller);
}