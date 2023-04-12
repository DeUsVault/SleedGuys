// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "ObstacleOverlap.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AObstacleOverlap : public AObstacle
{
	GENERATED_BODY()

public:
	void BindOverlap();

protected:
	UFUNCTION()
	virtual void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
};