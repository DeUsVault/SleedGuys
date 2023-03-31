// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleHandler.h"
#include "ObstacleArray.h"

AObstacleHandler::AObstacleHandler()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
}

void AObstacleHandler::BeginPlay()
{
	Super::BeginPlay();

	int32 ObstacleArrays = ObstacleActorsArray.Num();
	if (ObstacleArrays > 0)
	{
		for(AObstacleArray* ObstacleCollection : ObstacleActorsArray)
		{	
			if (bFirstIteration)
			{
				int32 ObstacleCollectionNumber = ObstacleCollection->ObstacleArray.Num();
				if (ObstacleCollectionNumber > 0)
				{
					SelectionOne = FMath::RandRange(0, ObstacleCollectionNumber - 1);
					ObstacleCollection->HandleObstacles(SelectionOne, PreviousSelectionOne, bFirstIteration);

					bFirstIteration = false;
				}
			}
			else
			{
				int32 ObstacleCollectionNumber = ObstacleCollection->ObstacleArray.Num();
				if (ObstacleCollectionNumber > 0)
				{	
					PreviousSelectionOne = SelectionOne;
					SelectionOne = FMath::RandRange(0, ObstacleCollectionNumber - 1);
					ObstacleCollection->HandleObstacles(SelectionOne, PreviousSelectionOne, bFirstIteration);
				}
			}
		}
	}
}

void AObstacleHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

