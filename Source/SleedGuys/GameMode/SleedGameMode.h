// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SleedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API ASleedGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	virtual void PlayerEliminated(class ASleedCharacter* ElimmedCharacter, class ASleedPlayerController* VictimController);
	virtual void RequestRespawn(ACharacter* ElimmedCharacter, AController* ElimmedController);

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override; // override this to change the player start selection during spawn
	
};
