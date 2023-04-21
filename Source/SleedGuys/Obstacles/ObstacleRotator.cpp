// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstacleRotator.h"

void AObstacleRotator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAllowRotation)
	{
		RotateActor(DeltaTime);
	}
}

void AObstacleRotator::RotateActor(float DeltaTime)
{
	FRotator Rotation = RootComponent->GetRelativeRotation();

	Rotation.Yaw += RotationSpeed * DeltaTime; // Rotate around X-axis

	RootComponent->SetRelativeRotation(Rotation);
}
