// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndLevelWidget.generated.h"

class UTextBlock;

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
	
};
