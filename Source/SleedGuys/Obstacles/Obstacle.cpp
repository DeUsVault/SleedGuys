// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
	ObstacleMesh->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

    StartLocation = GetActorLocation();
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    MoveUpDown(DeltaTime);
}

void AObstacle::MoveUpDown(float DeltaTime)
{
	CurrentLocation = GetActorLocation();
    CurrentLocation = FVector(CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z + (Speed * DeltaTime));
    SetActorLocation(CurrentLocation);

    float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
    if (DistanceMoved >= Distance)
    {
        Speed = -Speed;
        StartLocation = CurrentLocation;
    }
}
