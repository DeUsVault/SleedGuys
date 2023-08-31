// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelAudioActor.generated.h"

class USoundCue;
class UAudioComponent;

UCLASS()
class SLEEDGUYS_API ALevelAudioActor : public AActor
{
	GENERATED_BODY()
	
public:
	ALevelAudioActor();

	void ChangeSound();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* AudioSceneComponent;

	UPROPERTY(VisibleAnywhere)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditInstanceOnly)
	TArray<USoundCue*> AudioChoices;

	int32 AudioCounter = 0;

	int32 NumberOfAudios = 0;

};
