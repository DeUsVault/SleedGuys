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
					ObstacleCollection->HandleObstacles(bFirstIteration, SelectionOne, PreviousSelectionOne);

					bFirstIteration = false;
					PreviousSelectionOne = SelectionOne;
				}
			}
			else
			{
				int32 ObstacleCollectionNumber = ObstacleCollection->ObstacleArray.Num();
				if (ObstacleCollectionNumber > 0)
				{	
					// Calculate the minimum and maximum values for the new selection
					int32 MinSelection = FMath::Max(PreviousSelectionOne - 1, 0);
					int32 MaxSelection = FMath::Min(PreviousSelectionOne + 1, ObstacleCollectionNumber - 1);

					// Select a random number within the range of MinSelection to MaxSelection
					int32 NewSelection = FMath::RandRange(MinSelection, MaxSelection);

					ObstacleCollection->HandleObstacles(bFirstIteration, NewSelection, PreviousSelectionOne);

					PreviousSelectionOne = NewSelection;
				}
			}
		}
	}
}

void AObstacleHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

