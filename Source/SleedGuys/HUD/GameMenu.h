// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameMenu.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class SLEEDGUYS_API UGameMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResumeButtonText;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ExitButtonText;

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void ResumeButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();
	
};
