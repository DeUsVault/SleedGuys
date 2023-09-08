// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedHUD.h"
#include "GameFramework/PlayerController.h"
#include "CharacterOverlay.h"
#include "ButtonPresser.h"
#include "GameMenu.h"
#include "EndLevelWidget.h"

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

void ASleedHUD::HandleStunWidgetHUD(bool bCreate)
{	
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && ButtonPresserClass)
	{	
		if (bCreate)
		{	
			if (ButtonPresser)
			{	
				// we need to remove the previous widget if it existed
				ButtonPresser->RemoveFromViewport();
				ButtonPresser = nullptr;
			} 
			ButtonPresser = CreateWidget<UButtonPresser>(PlayerController, ButtonPresserClass);
			if (ButtonPresser)
			{
				ButtonPresser->AddToViewport();
			}
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

UGameMenu* ASleedHUD::HandleGameWidget()
{	
	APlayerController* PlayerController = GetOwningPlayerController();
	if (!PlayerController)
	{
		return nullptr;
	}

	if (GameMenu && GameMenu->IsInViewport())
	{
		// The widget is already in the viewport, so destroy it
		GameMenu->RemoveFromViewport();
		GameMenu = nullptr; // Set the pointer to nullptr since the widget is destroyed

		return GameMenu;
	}
	else
	{
		// The widget is not in the viewport, so create and add it
		GameMenu = CreateWidget<UGameMenu>(PlayerController, GameMenuWidgetClass);
		if (GameMenu)
		{
			GameMenu->AddToViewport();
			return GameMenu;
		}
	}

	return nullptr;
}

void ASleedHUD::AddEndLevelWidget()
{
	APlayerController* PlayerController = GetOwningPlayerController();
	if (PlayerController && EndLevelWidgetClass)
	{
		EndLevelWidget = CreateWidget<UEndLevelWidget>(PlayerController, EndLevelWidgetClass);
		if (EndLevelWidget)
		{
			EndLevelWidget->AddToViewport();
		}
	}
}

