// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedHUD.h"
#include "GameFramework/PlayerController.h"
#include "CharacterOverlay.h"
#include "ButtonPresser.h"

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

	ButtonPresser = CreateWidget<UButtonPresser>(PlayerController, ButtonPresserClass);
	ButtonPresser->AddToViewport();
}

void ASleedHUD::HandleStunWidgetHUD(bool bCreate)
{	
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && ButtonPresserClass)
	{	
		if (bCreate)
		{
			ButtonPresser = CreateWidget<UButtonPresser>(PlayerController, ButtonPresserClass);
			ButtonPresser->AddToViewport();
		}
		else
		{	
			if (ButtonPresser)
			{
				ButtonPresser->RemoveFromViewport();
			}
		}
	}
}

