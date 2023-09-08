#include "EndLevelWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SleedGuys/GameMode/SleedGameMode.h"

bool UEndLevelWidget::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	bIsFocusable = true;

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

void UEndLevelWidget::RestartButtonClicked()
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

void UEndLevelWidget::ExitButtonClicked()
{
	UGameplayStatics::OpenLevel(this, MainMenuMap);
}

void UEndLevelWidget::DynamicSetup(int32 Time, int32 Deaths, int32 Coins)
{
	int32 Minutes = FMath::FloorToInt(Time / 60.f);
	int32 Seconds = Time - Minutes * 60;
	FString CompletionTime = FString::Printf(TEXT("Time: %02d:%02d"), Minutes, Seconds);
	FString TotalDeaths = FString::Printf(TEXT("Deaths: %d"), Deaths);
	FString CoinsCollected = FString::Printf(TEXT("Coins: %d"), Coins);

	TimeText->SetText(FText::FromString(CompletionTime));
	DeathText->SetText(FText::FromString(TotalDeaths));
	CoinsText->SetText(FText::FromString(CoinsCollected));

	// disable controller input

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = GetOwningPlayer();
		if (Controller)
		{
			FInputModeUIOnly InputModeData;
			InputModeData.SetWidgetToFocus(TakeWidget());
			InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			Controller->SetInputMode(InputModeData);
			Controller->SetShowMouseCursor(true);

			Controller->StopMovement();
		}
	}
}
