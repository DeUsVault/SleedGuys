// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedHUD.h"
#include "GameFramework/PlayerController.h"
#include "CharacterOverlay.h"

void ASleedHUD::BeginPlay()
{
	Super::BeginPlay();

	AddCharacterOverlay();
}

void ASleedHUD::AddCharacterOverlay()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && CharacterOverlayClass)
	{
		CharacterOverlay = CreateWidget<UCharacterOverlay>(PlayerController, CharacterOverlayClass);
		CharacterOverlay->AddToViewport();
	}
}

