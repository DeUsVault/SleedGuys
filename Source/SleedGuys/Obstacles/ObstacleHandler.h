// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleHandler.generated.h"

class AObstacleArray;

UCLASS()
class SLEEDGUYS_API AObstacleHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleHandler();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditInstanceOnly)
	TArray<AObstacleArray*> ObstacleActorsArray;

	int32 SelectionOne = 0;
	int32 SelectionTwo = 0;
	int32 PreviousSelectionOne = 0;
	int32 PreviousSelectionTwo = 0;
	bool bFirstIteration = true;

protected:
	virtual void BeginPlay() override;

public:	

};
