// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedPlayerState.h"
#include "SleedGuys/PlayerController/SleedPlayerController.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "Net/UnrealNetwork.h"

void ASleedPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASleedPlayerState, Gold);
	DOREPLIFETIME_CONDITION(ASleedPlayerState, LastCheckpoint, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(ASleedPlayerState, Deaths, COND_OwnerOnly);
}

void ASleedPlayerState::AddGold(int32 AmountOfGold)
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("gold added"));
	Gold += AmountOfGold;
	SleedCharacter = SleedCharacter == nullptr ? Cast<ASleedCharacter>(GetPawn()) : SleedCharacter;
	if (SleedCharacter)
	{
		SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(SleedCharacter->Controller) : SleedPlayerController;
		if (SleedPlayerController)
		{
			SleedPlayerController->SetHUDGold(Gold);
		}
	}
}

void ASleedPlayerState::OnRep_Gold()
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("gold replicate"));
	SleedCharacter = SleedCharacter == nullptr ? Cast<ASleedCharacter>(GetPawn()) : SleedCharacter;
	if (SleedCharacter)
	{
		SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(SleedCharacter->Controller) : SleedPlayerController;
		if (SleedPlayerController)
		{
			SleedPlayerController->SetHUDGold(Gold);
		}
	}
}

void ASleedPlayerState::AddDeath()
{
	Deaths = Deaths + 1;
	SleedCharacter = SleedCharacter == nullptr ? Cast<ASleedCharacter>(GetPawn()) : SleedCharacter;
	if (SleedCharacter)
	{
		SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(SleedCharacter->Controller) : SleedPlayerController;
		if (SleedPlayerController)
		{
			SleedPlayerController->SetHUDDeaths(Deaths);
		}
	}
}

void ASleedPlayerState::OnRep_Deaths()
{
	SleedCharacter = SleedCharacter == nullptr ? Cast<ASleedCharacter>(GetPawn()) : SleedCharacter;
	if (SleedCharacter)
	{
		SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(SleedCharacter->Controller) : SleedPlayerController;
		if (SleedPlayerController)
		{
			SleedPlayerController->SetHUDDeaths(Deaths);
		}
	}
}

void ASleedPlayerState::SetLastCheckpoint(APlayerStart* Checkpoint)
{
	LastCheckpoint = Checkpoint;
}
