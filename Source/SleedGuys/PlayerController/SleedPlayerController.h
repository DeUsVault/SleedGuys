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
	virtual void Tick(float DeltaTime) override;

	void SetHUDHealth(float Health, float MaxHealth);
	void SetHUDStamina(float Stamina, float MaxStamina);
	void SetHUDGold(int32 CoinsNum);
	void HandleStunWidget(bool bCreate);
	void SetHUDStunButtons(int32 num);
	void SetGameMenuWidget();
	void SetHUDMatchTime(float Time);
	void SetHUDDeaths(int32 Deaths);
	void SetEndLevelWidget();

protected:
	virtual void BeginPlay() override;

	void SetHUDTime();

private:
	ASleedHUD* SleedHUD;
};
