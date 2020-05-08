// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_MainMenu.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

void UUI_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	MiniGameInstance = Cast<UMiniGameBananzaGameInstance>(GetGameInstance());
	if (MiniGameInstance)
	{
		MiniGameInstance->ResetScores();
		MiniGameInstance->SetIsGamemodeSelection(false);
	}

	InitializeComponents();
}

void UUI_MainMenu::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	HandleAction(DeltaTime);

	HandleMusicLoop(DeltaTime);
}

void UUI_MainMenu::InitializeComponents()
{
	if (ButtonStart)
	{
		ButtonStart->OnClicked.AddDynamic(this, &UUI_MainMenu::OnStart);
		ButtonStart->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonGameModes)
	{
		ButtonGameModes->OnClicked.AddDynamic(this, &UUI_MainMenu::OnGameModeSelection);
		ButtonGameModes->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonInstructions)
	{
		ButtonInstructions->OnClicked.AddDynamic(this, &UUI_MainMenu::OnInstructions);
		ButtonInstructions->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonSettings)
	{
		ButtonSettings->OnClicked.AddDynamic(this, &UUI_MainMenu::OnSettings);
		ButtonSettings->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}

	if (ButtonExit)
	{
		ButtonExit->OnClicked.AddDynamic(this, &UUI_MainMenu::OnExit);
		ButtonExit->OnHovered.AddDynamic(this, &UUI_MainMenu::OnHoverButton);
	}
}

void UUI_MainMenu::HandleAction(float DeltaTime)
{
	if (Action)
	{
		if (ActionTimer <= 0)
		{
			Action(this);
			Action = nullptr;
		}
		else
		{
			ActionTimer -= DeltaTime;
		}
	}
}

void UUI_MainMenu::HandleMusicLoop(float DeltaTime)
{
	if (MusicLoopTimer <= 0 && scMusic)
	{
		MusicLoopTimer = scMusic->GetDuration();
		PlaySound(scMusic);
	}
	else
	{
		MusicLoopTimer -= DeltaTime;
	}
}

void UUI_MainMenu::PlaySoundAndActionWhenFinished(USoundBase* SoundBase, void(*action)(UUI_MainMenu*))
{
	if (SoundBase && action && !Action)
	{
		ActionTimer = SoundBase->GetDuration();
		Action = action;
		PlaySound(SoundBase);
	}
}

void UUI_MainMenu::OnStart()
{
	if (scStart)
	{
		PlaySoundAndActionWhenFinished(scStart, [](UUI_MainMenu* This) 
			{
				This->MiniGameInstance->SetGameMode(GameModeLevels::Bomberman);
			});
	}
}

void UUI_MainMenu::OnGameModeSelection()
{
	if (scClick_High)
	{
		PlaySoundAndActionWhenFinished(scClick_High, [](UUI_MainMenu* This)
			{
				const UWorld* World = This->GetWorld();
				if (World)
				{
					This->MiniGameInstance->SetCurrentLevel(GameModeLevels::Bomberman);
					UGameplayStatics::OpenLevel(World, FName(TEXT("GameMode_Selection_Menu")));
				}
			});
	}
}

void UUI_MainMenu::OnInstructions()
{
	OnClickButton();
}

void UUI_MainMenu::OnSettings()
{
	OnClickButton();
}

void UUI_MainMenu::OnExit()
{
	if (scExit)
	{
		PlaySoundAndActionWhenFinished(scExit, [](UUI_MainMenu* This) 
			{
				TEnumAsByte<EQuitPreference::Type> pref = TEnumAsByte<EQuitPreference::Type>(EQuitPreference::Quit);
				UKismetSystemLibrary::QuitGame(This->GetWorld(), nullptr, pref, false);
			});
	}
}

void UUI_MainMenu::OnHoverButton()
{
	if (scHover)
	{
		PlaySound(scHover);
	}
}

void UUI_MainMenu::OnClickButton()
{
	if (scClick_High)
	{
		PlaySound(scClick_High);
	}
}

void UUI_MainMenu::OnClickBackButton()
{
	if (scClick_Low)
	{
		PlaySound(scClick_Low);
	}
}
