// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleArray.h"
#include "Obstacle.h"

AObstacleArray::AObstacleArray()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AObstacleArray::BeginPlay()
{
	Super::BeginPlay();
}

void AObstacleArray::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObstacleArray::HandleObstacles(bool bFirstIteration, int32 SelectionOne, int32 PreviousSelectionOne)
{
	int32 ObstaclesNumber = ObstacleArray.Num();
	if (ObstaclesNumber > 0)
	{	
		if (bFirstIteration) // during the first iteration we can choose whichever actor randomly
		{	
			if (ObstacleArray[SelectionOne])
			{
				ObstacleArray[SelectionOne]->Destroy();
			}
		}
		else // during the next iterations we must choose actors that are in a range of [-1,1] from the previous selected actors
		{
			if (ObstacleArray[SelectionOne])
			{
				ObstacleArray[SelectionOne]->Destroy();
			}
		}
	}
}

