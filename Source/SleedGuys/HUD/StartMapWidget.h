// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMapWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API UStartMapWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UButton* SinglePlay;

	UPROPERTY(meta = (BindWidget))
	UButton* MultiPlay;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitButton;

	UFUNCTION(BlueprintCallable)
	void MenuSetup();

protected:
	virtual bool Initialize() override;

private:
	UFUNCTION()
	void SinglePlayButtonClicked();

	UFUNCTION()
	void MultiPlayButtonClicked();

	UFUNCTION()
	void ExitButtonClicked();

	UPROPERTY(EditAnywhere)
	TArray<FName> SingleMaps;
	
};
