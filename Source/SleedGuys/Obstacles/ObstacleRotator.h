// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "ObstacleRotator.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AObstacleRotator : public AObstacle
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

private:
	//
	// rotate object logic
	//
	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	bool bAllowRotation = false;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	float RotationSpeed = 200.f;

	void RotateActor(float DeltaTime);
	
};
