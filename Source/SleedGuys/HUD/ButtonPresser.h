// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonPresser.generated.h"

class UTextBlock;
class UButton;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API UButtonPresser : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ButtonText;

	UPROPERTY(meta = (BindWidget))
	UButton* FirstButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SecondButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ThirdButton;

protected:
	virtual void NativeConstruct() override;
	
};
