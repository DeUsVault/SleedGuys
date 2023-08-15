#include "GameMenu.h"
#include "Components/Button.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SleedGuys/PlayerController/SleedPlayerController.h"
#include "SleedGuys/GameMode/SleedGameMode.h"

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
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &ThisClass::RestartButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &ThisClass::ExitButtonClicked);
	}

	return true;
}

void UGameMenu::ResumeButtonClicked()
{
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

void UGameMenu::RestartButtonClicked()
{
	ASleedGameMode* SleedGameMode = GetWorld()->GetAuthGameMode<ASleedGameMode>();
	APlayerController* Controller = GetOwningPlayer();

	if (SleedGameMode && Controller)
	{
		SleedGameMode->RestartGame();
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->bShowMouseCursor = false;
	}
}

void UGameMenu::ExitButtonClicked()
{
	APlayerController* Controller = GetOwningPlayer();
	if (Controller)
	{
		UKismetSystemLibrary::QuitGame(GetWorld(), Controller, EQuitPreference::Quit, true);
	}
}