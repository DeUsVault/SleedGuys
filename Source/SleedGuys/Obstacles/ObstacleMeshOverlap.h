// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "ObstacleMeshOverlap.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AObstacleMeshOverlap : public AObstacle
{
	GENERATED_BODY()
	
public:
	AObstacleMeshOverlap();

	virtual void BindOverlap() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnMeshOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnMeshEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* OverlapMesh;
};
