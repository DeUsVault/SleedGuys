// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleArray.h"
#include "Obstacle.h"
#include "ObstacleMeshOverlap.h"

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

void AObstacleArray::HandleObstacles(int32 Selection)
{
	int32 ObstaclesNumber = ObstacleArray.Num();
	if (ObstaclesNumber > 0 && Selection < ObstaclesNumber)
	{	
		if (ObstacleArray[Selection])
		{
			ObstacleArray[Selection]->Destroy();
		}
	}
}

void AObstacleArray::HandleObstaclesNew(int32 Selection)
{
	int32 ObstaclesNumber = ObstacleArray.Num();
	if (ObstaclesNumber > 0 && Selection < ObstaclesNumber)
	{
		if (ObstacleArray[Selection])
		{	
			AObstacleMeshOverlap* ObstacleOverlap = Cast<AObstacleMeshOverlap>(ObstacleArray[Selection]);
			if (ObstacleOverlap)
			{
				ObstacleOverlap->BindOverlap();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
			}
		}
	}
}

