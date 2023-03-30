// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedPlayerController.h"
#include "SleedGuys/HUD/SleedHUD.h"
#include "SleedGuys/HUD/CharacterOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void ASleedPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SleedHUD = Cast<ASleedHUD>(GetHUD());
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

