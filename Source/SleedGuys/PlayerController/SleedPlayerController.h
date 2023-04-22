// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SleedPlayerController.generated.h"

class ASleedHUD;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API ASleedPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDStamina(float Stamina, float MaxStamina);
	void SetHUDGold(int32 CoinsNum);
	void HandleStunWidget(bool bCreate);
	void SetHUDStunButtons(int32 num);
protected:
	virtual void BeginPlay() override;

private:
	ASleedHUD* SleedHUD;
};
