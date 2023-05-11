// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "ObstacleOverlap.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AObstacleOverlap : public AObstacle
{
	GENERATED_BODY()

public:
	AObstacleOverlap();

	// bind overlap is called on the actor from another actor, for example from the ObstacleArray
	virtual void BindOverlap() override;

protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* OverlapBox;

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