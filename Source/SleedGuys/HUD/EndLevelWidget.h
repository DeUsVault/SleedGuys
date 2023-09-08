// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndLevelWidget.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API UEndLevelWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* EndLevelText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TimeText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CoinsText;

	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	void DynamicSetup(int32 Time, int32 Deaths, int32 Coins);

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void RestartButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();

	UPROPERTY(EditAnywhere)
	FName MainMenuMap;
	
};
