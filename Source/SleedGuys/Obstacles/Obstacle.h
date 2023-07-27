// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class SLEEDGUYS_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();
	virtual void Tick(float DeltaTime) override;

	virtual void BindOverlap();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastUpdateLocation(FVector Location);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ObstacleMesh;

private:
	FVector StartLocation;

	FVector CurrentLocation;

	//
	// move object logic
	//
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bAllowMovement = true;

    UPROPERTY(EditAnywhere, Category = "Obstacle Movement")
    float Speed = 200.f;

    UPROPERTY(EditAnywhere, Category = "Obstacle Movement")
    float Distance = 200.f;

	UPROPERTY(EditAnywhere, Category = "Obstacle Movement")
	bool bMoveOnX = false;

	UPROPERTY(EditAnywhere, Category = "Obstacle Movement")
	bool bMoveOnY = false;

	UPROPERTY(EditAnywhere, Category = "Obstacle Movement")
	bool bMoveOnZ = true;

	void MoveOnAxis(float DeltaTime);

	//
	// rotate object logic
	//
	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	bool bAllowRotation = false;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	float RotationSpeed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	bool bReverseRotation = false;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	double RotationMaxDegrees = 80.f;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	bool bRotateOnX = false;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	bool bRotateOnY = false;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	bool bRotateOnZ = true;

	void RotateActor(float DeltaTime);

public:	

};
