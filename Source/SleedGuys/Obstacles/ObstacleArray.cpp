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
			ObstacleArray[Selection]->Destroy();
		}
	}
}

