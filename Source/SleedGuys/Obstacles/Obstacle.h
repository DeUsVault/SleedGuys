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

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* ObstacleMesh;

	FVector StartLocation;
	FVector CurrentLocation;

    UPROPERTY(EditAnywhere, Category = "Obstacle Movement")
    float Speed = 200.f;

    UPROPERTY(EditAnywhere, Category = "Obstacle Movement")
    float Distance = 200.f;

	void MoveUpDown(float DeltaTime);

public:	

};
