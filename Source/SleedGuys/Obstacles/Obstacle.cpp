// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "Net/UnrealNetwork.h"

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

    if (bAllowMovement && HasAuthority())
    {
        MoveOnAxis(DeltaTime);
    }

    if (bAllowRotation)
    {
        RotateActor(DeltaTime);
    }
}

void AObstacle::MoveOnAxis(float DeltaTime)
{
    FVector TickLocation = GetActorLocation();

    float LocationX = TickLocation.X;
    float LocationY = TickLocation.Y;
    float LocationZ = TickLocation.Z;

    if (bMoveOnX) LocationX = LocationX + (Speed * DeltaTime);
    if (bMoveOnY) LocationY = LocationY + (Speed * DeltaTime);
    if (bMoveOnZ) LocationZ = LocationZ + (Speed * DeltaTime);

    CurrentLocation = FVector(LocationX, LocationY, LocationZ);
    MulticastUpdateLocation(CurrentLocation);

    float DistanceMoved = FVector::Dist(StartLocation, CurrentLocation);
    if (DistanceMoved >= Distance)
    {
        Speed = -Speed;
        StartLocation = CurrentLocation;
    }
}

void AObstacle::MulticastUpdateLocation_Implementation(FVector Location)
{
    SetActorLocation(Location);
}

void AObstacle::RotateActor(float DeltaTime)
{
    FRotator Rotation = RootComponent->GetRelativeRotation();

    double RotationX = Rotation.Roll;
    double RotationY = Rotation.Pitch;
    double RotationZ = Rotation.Yaw;

    if (bRotateOnX)
    {
        RotationX += RotationSpeed * DeltaTime;

        if (bReverseRotation)
        {
            if (RotationX > RotationMaxDegrees)
            {
                RotationX = (RotationMaxDegrees * 2) - RotationX; // Rotate towards the negative limit
                RotationSpeed = -RotationSpeed; // Reverse rotation direction
            }
            else if (RotationX < -RotationMaxDegrees)
            {
                RotationX = -(RotationMaxDegrees * 2) - RotationX; // Rotate towards the positive limit
                RotationSpeed = -RotationSpeed; // Reverse rotation direction
            }
        }
    }

    if (bRotateOnY)
    {
        RotationY += RotationSpeed * DeltaTime;
        
        if (bReverseRotation) 
        {
            if (RotationY > RotationMaxDegrees)
            {
                RotationY = (RotationMaxDegrees * 2) - RotationY;
                RotationSpeed = -RotationSpeed;
            }
            else if (RotationY < -RotationMaxDegrees)
            {
                RotationY = -(RotationMaxDegrees * 2) - RotationY;
                RotationSpeed = -RotationSpeed;
            }
        }
    }

    if (bRotateOnZ)
    {
        RotationZ += RotationSpeed * DeltaTime;

        if (bReverseRotation)
        {
            if (RotationZ > RotationMaxDegrees)
            {
                RotationZ = (RotationMaxDegrees * 2) - RotationZ;
                RotationSpeed = -RotationSpeed;
            }
            else if (RotationZ < -RotationMaxDegrees)
            {
                RotationZ = -(RotationMaxDegrees * 2) - RotationZ;
                RotationSpeed = -RotationSpeed;
            }
        }
    }

    Rotation.Roll = RotationX;
    Rotation.Pitch = RotationY;
    Rotation.Yaw = RotationZ;

    RootComponent->SetRelativeRotation(Rotation);
}

void AObstacle::BindOverlap()
{
    GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("AObstacle basic BindOverlap function"));
}
