// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedPlayerController.h"
#include "SleedGuys/HUD/SleedHUD.h"
#include "SleedGuys/HUD/CharacterOverlay.h"
#include "SleedGuys/HUD/ButtonPresser.h"
#include "SleedGuys/HUD/GameMenu.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Net/UnrealNetwork.h"

void ASleedPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SleedHUD = Cast<ASleedHUD>(GetHUD());
}

void ASleedPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetHUDTime();
}

void ASleedPlayerController::SetHUDHealth(float Health, float MaxHealth)
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;

	bool bHUDValid = SleedHUD &&
		SleedHUD->CharacterOverlay &&
		SleedHUD->CharacterOverlay->HealthBar &&
		SleedHUD->CharacterOverlay->HealthText;
	if (bHUDValid)
	{
		const float HealthPercent = Health / MaxHealth;
		SleedHUD->CharacterOverlay->HealthBar->SetPercent(HealthPercent);
		
		FString HealthText = FString::Printf(TEXT("%.2f%%"), (HealthPercent * 100));
		SleedHUD->CharacterOverlay->HealthText->SetText(FText::FromString(HealthText));
	}
}

void ASleedPlayerController::SetHUDStamina(float Stamina, float MaxStamina)
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;

	bool bHUDValid = SleedHUD &&
		SleedHUD->CharacterOverlay &&
		SleedHUD->CharacterOverlay->StaminaBar &&
		SleedHUD->CharacterOverlay->StaminaText;
	if (bHUDValid)
	{
		const float StaminaPercent = Stamina / MaxStamina;
		SleedHUD->CharacterOverlay->StaminaBar->SetPercent(StaminaPercent);
	}
}

void ASleedPlayerController::SetHUDGold(int32 CoinsNum)
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;

	bool bHUDValid = SleedHUD &&
		SleedHUD->CharacterOverlay &&
		SleedHUD->CharacterOverlay->CoinText;
	if (bHUDValid)
	{
		FString CoinText = FString::FromInt(CoinsNum);
		SleedHUD->CharacterOverlay->CoinText->SetText(FText::FromString(CoinText));
	}
}

void ASleedPlayerController::HandleStunWidget(bool bCreate)
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;

	if (SleedHUD)
	{
		SleedHUD->HandleStunWidgetHUD(bCreate);
	}
}

void ASleedPlayerController::SetHUDStunButtons(int32 num)
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;

	bool bHUDValid = SleedHUD &&
		SleedHUD->ButtonPresser &&
		SleedHUD->ButtonPresser->FirstButton &&
		SleedHUD->ButtonPresser->SecondButton &&
		SleedHUD->ButtonPresser->ThirdButton;

	if (bHUDValid)
	{
		switch (num) {
		case 1:
			SleedHUD->ButtonPresser->FirstButton->SetBackgroundColor(FLinearColor::Green);
			break;
		case 2:
			SleedHUD->ButtonPresser->SecondButton->SetBackgroundColor(FLinearColor::Green);
			break;
		case 3:
			SleedHUD->ButtonPresser->ThirdButton->SetBackgroundColor(FLinearColor::Green);
			break;
		default:
			break;
		}
	}
}

void ASleedPlayerController::SetGameMenuWidget()
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;

	if (SleedHUD)
	{
		auto Widget = SleedHUD->HandleGameWidget();

		if(Widget)
		{
			// disable input/movement and stuff
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(Widget->TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			SetInputMode(InputModeData);
			this->bShowMouseCursor = true;

			SetPause(true); // works on singleplayer only
		}
		else
		{
			// reset input/movement and stuff back to normal
			SetInputMode(FInputModeGameOnly());
			this->bShowMouseCursor = false;

			SetPause(false); // works on singleplayer only
		}
	}
}

void ASleedPlayerController::SetHUDTime()
{
	uint32 Seconds = FMath::CeilToInt(GetWorld()->GetTimeSeconds());
	SetHUDMatchTime(Seconds);
}

void ASleedPlayerController::SetHUDMatchTime(float MatchTime)
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;
	bool bHUDValid = SleedHUD &&
		SleedHUD->CharacterOverlay &&
		SleedHUD->CharacterOverlay->MatchTimeText;
	if (bHUDValid)
	{
		int32 Minutes = FMath::FloorToInt(MatchTime / 60.f);
		int32 Seconds = MatchTime - Minutes * 60;

		FString CountdownText = FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds);
		SleedHUD->CharacterOverlay->MatchTimeText->SetText(FText::FromString(CountdownText));
	}
}

void ASleedPlayerController::SetHUDDeaths(int32 Deaths)
{
	SleedHUD = SleedHUD == nullptr ? Cast<ASleedHUD>(GetHUD()) : SleedHUD;
	bool bHUDValid = SleedHUD &&
		SleedHUD->CharacterOverlay &&
		SleedHUD->CharacterOverlay->DeathsNumText;
	if (bHUDValid)
	{	
		FString DeathText = FString::Printf(TEXT("Deaths : %d"), Deaths);
		SleedHUD->CharacterOverlay->DeathsNumText->SetText(FText::FromString(DeathText));
	}
}

