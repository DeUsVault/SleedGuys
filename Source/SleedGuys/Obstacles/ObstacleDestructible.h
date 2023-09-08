// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Obstacle.h"
#include "ObstacleDestructible.generated.h"

class USphereComponent;
class UGeometryCollectionComponent;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AObstacleDestructible : public AObstacle
{
	GENERATED_BODY()

public:
	AObstacleDestructible();

	virtual void BindOverlap() override;

protected:
	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);

private:
	UPROPERTY(VisibleAnywhere)
	USphereComponent* AreaSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UGeometryCollectionComponent* GeometryCollection;

	// destroy actor
	void HandleDestruction();

	UPROPERTY(EditAnywhere)
	float DestroyTimer = 3.0f;

	FTimerHandle DestroyTimerHandle;
	
};
