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

    if (bAllowMovement)
    {
        MoveOnAxis(DeltaTime);
    }
}

void AObstacle::MoveOnAxis(float DeltaTime)
{
	CurrentLocation = GetActorLocation();

    float LocationX = CurrentLocation.X;
    float LocationY = CurrentLocation.Y;
    float LocationZ = CurrentLocation.Z;

    if (bMoveOnX) LocationX = LocationX + (Speed * DeltaTime);
    if (bMoveOnY) LocationY = LocationY + (Speed * DeltaTime);
    if (bMoveOnZ) LocationZ = LocationZ + (Speed * DeltaTime);

    CurrentLocation = FVector(LocationX, LocationY, LocationZ);
    SetActorLocation(CurrentLocation);

    float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
    if (DistanceMoved >= Distance)
    {
        Speed = -Speed;
        StartLocation = CurrentLocation;
    }
}
