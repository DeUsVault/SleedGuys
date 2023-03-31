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

void AObstacleArray::HandleObstacles(int32 SelectionOne, int32 PreviousSelectionOne, bool bFirstIteration)
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
			// Calculate the minimum and maximum values for the new selection
			int32 MinSelection = FMath::Max(PreviousSelectionOne - 1, 0);
			int32 MaxSelection = FMath::Min(PreviousSelectionOne + 1, ObstacleArray.Num() - 1);

			// Select a random number within the range of MinSelection to MaxSelection
			int32 NewSelection = FMath::RandRange(MinSelection, MaxSelection);

			if (ObstacleArray[NewSelection])
			{
				ObstacleArray[NewSelection]->Destroy();
			}
		}
	}
}

