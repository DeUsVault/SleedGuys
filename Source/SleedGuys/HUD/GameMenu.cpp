#include "GameMenu.h"
#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "SleedGuys/PlayerController/SleedPlayerController.h"
#include "Kismet/KismetSystemLibrary.h"

bool UGameMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	bIsFocusable = true;

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &ThisClass::ResumeButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitButtonClicked);
	}

	return true;
}

void UGameMenu::ResumeButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("resume game mode"));
	APlayerController* Controller = GetOwningPlayer();
	if (Controller)
	{
		ASleedPlayerController* SleedPlayerController = Cast<ASleedPlayerController>(Controller);
		if (SleedPlayerController)
		{
			SleedPlayerController->SetGameMenuWidget();
		}
	}
}

void UGameMenu::ExitButtonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("exit game mode"));
	APlayerController* Controller = GetOwningPlayer();
	if (Controller)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, true);
	}
}