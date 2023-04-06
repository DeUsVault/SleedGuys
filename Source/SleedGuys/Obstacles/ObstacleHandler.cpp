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

	if (bUseNewHandler)
	{
		HandleObjectsNew();
	}
	else
	{
		HandleObjects();
	}
}

void AObstacleHandler::HandleObjects()
{
	int32 ObstacleArrays = ObstacleActorsArray.Num();
	if (ObstacleArrays > 0)
	{
		for (AObstacleArray* ObstacleCollection : ObstacleActorsArray)
		{
			if (bFirstIteration)
			{
				int32 ObstacleCollectionNumber = ObstacleCollection->ObstacleArray.Num();
				if (ObstacleCollectionNumber > 0)
				{
					SelectionOne = FMath::RandRange(0, ObstacleCollectionNumber - 1);

					// Select the second random number 
					if ((ObstacleCollectionNumber - 1) > 0) // we need to have more than one possible selections else we will loop forever
					{
						do
						{
							SelectionTwo = FMath::RandRange(0, ObstacleCollectionNumber - 1);
						} while (SelectionTwo == SelectionOne);
					}
					else
					{
						SelectionTwo = SelectionOne;
					}

					ObstacleCollection->HandleObstacles(SelectionOne);
					ObstacleCollection->HandleObstacles(SelectionTwo);

					bFirstIteration = false;
					PreviousSelectionOne = SelectionOne;
					PreviousSelectionTwo = SelectionTwo;
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
					SelectionOne = FMath::RandRange(MinSelection, MaxSelection);
					// Select the second random number 
					if (PreviousSelectionOne == PreviousSelectionTwo)
					{
						if ((MaxSelection - MinSelection) > 0)
						{
							do
							{
								SelectionTwo = FMath::RandRange(MinSelection, MaxSelection);
							} while (SelectionTwo == SelectionOne);
						}
						else
						{
							SelectionTwo = SelectionOne;
						}
					}
					else
					{
						// Calculate the minimum and maximum values for the new selection
						MinSelection = FMath::Max(PreviousSelectionTwo - 1, 0);
						MaxSelection = FMath::Min(PreviousSelectionTwo + 1, ObstacleCollectionNumber - 1);

						if ((MaxSelection - MinSelection) > 0)
						{
							do
							{
								SelectionTwo = FMath::RandRange(MinSelection, MaxSelection);
							} while (SelectionTwo == SelectionOne);
						}
						else
						{
							MinSelection = FMath::Max(PreviousSelectionOne - 1, 0);
							MaxSelection = FMath::Min(PreviousSelectionOne + 1, ObstacleCollectionNumber - 1);

							if ((MaxSelection - MinSelection) > 0)
							{
								do
								{
									SelectionTwo = FMath::RandRange(MinSelection, MaxSelection);
								} while (SelectionTwo == SelectionOne);
							}
							else
							{
								SelectionTwo = SelectionOne;
							}
						}
					}

					ObstacleCollection->HandleObstacles(SelectionOne);
					ObstacleCollection->HandleObstacles(SelectionTwo);

					PreviousSelectionOne = SelectionOne;
					PreviousSelectionTwo = SelectionTwo;
				}
			}
		}
	}
}

void AObstacleHandler::HandleObjectsNew()
{
	int32 ObstacleArrays = ObstacleActorsArray.Num();
	if (ObstacleArrays > 0)
	{
		for (AObstacleArray* ObstacleCollection : ObstacleActorsArray)
		{   
			int32 ObstacleCollectionNumber = ObstacleCollection->ObstacleArray.Num();
			if (ObstacleCollectionNumber > 0)
			{	
				int32 SafeLimit = FMath::CeilToInt(ObstacleCollectionNumber / SafeLimitDivider);

				if (bFirstIteration)
				{	
					TArray<int32> NewSafeSpots;

					do
					{
						int32 Selection = FMath::RandRange(0, ObstacleCollectionNumber - 1);
						NewSafeSpots.AddUnique(Selection);

					} while (NewSafeSpots.Num() < SafeLimit);

					for (int32 i = 0; i < ObstacleCollectionNumber; i++)
					{
						if (NewSafeSpots.Contains(i)) continue;

						ObstacleCollection->HandleObstaclesNew(i);
					}

					NextSafeSpots = NewSafeSpots;
					bFirstIteration = false;
				}
				else
				{	
					TArray<int32> NewSafeSpots;

					for (auto Num : NextSafeSpots)
					{
						int32 MinSelection = FMath::Max(Num - 1, 0);
						int32 MaxSelection = FMath::Min(Num + 1, ObstacleCollectionNumber - 1);

						int32 Selection = FMath::RandRange(MinSelection, MaxSelection);
						NewSafeSpots.AddUnique(Selection);
					}

					while (NewSafeSpots.Num() < SafeLimit)
					{
						int32 Selection = FMath::RandRange(0, ObstacleCollectionNumber - 1);
						NewSafeSpots.AddUnique(Selection);
					}

					for (int32 i = 0; i < ObstacleCollectionNumber; i++)
					{
						if (NewSafeSpots.Contains(i)) continue;

						ObstacleCollection->HandleObstaclesNew(i);
					}

					NextSafeSpots = NewSafeSpots;

				}
			}
		}
	}
}

void AObstacleHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

