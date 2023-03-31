// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObstacleArray.generated.h"

class AObstacle;

UCLASS()
class SLEEDGUYS_API AObstacleArray : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacleArray();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditInstanceOnly)
	TArray<AObstacle*> ObstacleArray;

	void HandleObstacles(int32 SelectionOne, int32 PreviousSelectionOne, bool bFirstIteration);

};
