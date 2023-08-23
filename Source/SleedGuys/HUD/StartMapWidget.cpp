// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMapWidget.h"
#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

bool UStartMapWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	bIsFocusable = true;

	if (SinglePlay)
	{
		SinglePlay->OnClicked.AddDynamic(this, &ThisClass::SinglePlayButtonClicked);
	}
	if (MultiPlay)
	{
		MultiPlay->OnClicked.AddDynamic(this, &ThisClass::MultiPlayButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitButtonClicked);
	}

	return true;
}

void UStartMapWidget::MenuSetup()
{
	AddToViewport();
	SetVisibility(ESlateVisibility::Visible);
	bIsFocusable = true;

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			PlayerController->SetInputMode(InputModeData);
			PlayerController->SetShowMouseCursor(true);
		}
	}
}

void UStartMapWidget::SinglePlayButtonClicked()
{	
	if (SingleMaps.IsValidIndex(0) && !SingleMaps[0].IsNone())
	{	
		UWorld* World = GetWorld();
		if (World)
		{
			APlayerController* PlayerController = World->GetFirstPlayerController();
			if (PlayerController)
			{
				PlayerController->SetInputMode(FInputModeGameOnly());
				PlayerController->SetShowMouseCursor(false);
			}
		}

		UGameplayStatics::OpenLevel(this, SingleMaps[0]);
	}
}

void UStartMapWidget::MultiPlayButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("multiplayer"));
}

void UStartMapWidget::ExitButtonClicked()
{
	APlayerController* Controller = GetOwningPlayer();
	if (Controller)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, true);
	}
}
