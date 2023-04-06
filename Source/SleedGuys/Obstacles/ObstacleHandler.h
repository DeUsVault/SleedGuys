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

protected:
	virtual void BeginPlay() override;

	void HandleObjects();

	void HandleObjectsNew();

	UPROPERTY(EditInstanceOnly, Category = "Handler Logic")
	TArray<AObstacleArray*> ObstacleActorsArray;

	UPROPERTY(EditInstanceOnly, Category = "Handler Logic")
	bool bUseNewHandler = true;

	UPROPERTY(EditInstanceOnly, Category = "Handler Logic")
	float SafeLimitDivider = 2.f;

	bool bFirstIteration = true;
	TArray<int32> NextSafeSpots;
	int32 SelectionOne = 0;
	int32 SelectionTwo = 0;
	int32 PreviousSelectionOne = 0;
	int32 PreviousSelectionTwo = 0;

public:	

};
