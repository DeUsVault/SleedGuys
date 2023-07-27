// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SleedPlayerState.generated.h"

class ASleedCharacter;
class ASleedPlayerController;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API ASleedPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void AddGold(int32 AmountOfGold);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Gold, VisibleAnywhere)
	int32 Gold;

	UFUNCTION()
	void OnRep_Gold();

private:
	ASleedCharacter* SleedCharacter;
	ASleedPlayerController* SleedPlayerController;
	
};
