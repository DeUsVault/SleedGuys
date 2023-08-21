// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SleedPlayerState.generated.h"

class ASleedCharacter;
class ASleedPlayerController;
class APlayerStart;

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
	void AddDeath();
	void SetLastCheckpoint(APlayerStart* Checkpoint);

protected:
	UPROPERTY(ReplicatedUsing = OnRep_Gold, VisibleAnywhere)
	int32 Gold;

	UFUNCTION()
	void OnRep_Gold();

	UPROPERTY(ReplicatedUsing = OnRep_Deaths, VisibleAnywhere)
	int32 Deaths = 0;

	UFUNCTION()
	void OnRep_Deaths();

private:
	ASleedCharacter* SleedCharacter;
	ASleedPlayerController* SleedPlayerController;

	UPROPERTY(Replicated)
	APlayerStart* LastCheckpoint = nullptr;

public:
	// Place for Getters/Setters only
	FORCEINLINE APlayerStart* getLastCheckpoint() { return this->LastCheckpoint; }
	
};
