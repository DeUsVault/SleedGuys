// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioParent.h"
#include "AudioTrigger.generated.h"

class ALevelAudioActor;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AAudioTrigger : public AActor
{
	GENERATED_BODY()

public:
	AAudioTrigger();

	void ChangeSoundTrigger();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* AudioSceneComponent;

	UPROPERTY(EditInstanceOnly)
	ALevelAudioActor* LevelAudioActor;
};
