// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SLEEDGUYS_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	APickup();
	virtual void Tick(float DeltaTime) override;
	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

private:
	//
	// pickup logic on overlap
	//
	UPROPERTY(EditAnywhere)
	USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere)
	USoundCue* PickupSound;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PickupMesh;

	FTimerHandle BindOverlapTimer;
	float BindOverlapTime = 0.25f;
	void BindOverlapTimerFinished();

	//
	// movable object logic
	//
	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bAllowMovement = false;

	FVector StartLocation;
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Distance = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bMoveOnX = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bMoveOnY = false;

	UPROPERTY(EditAnywhere, Category = "Movement")
	bool bMoveOnZ = true;

	void MoveOnAxis(float DeltaTime);

	//
	// rotate object logic
	//
	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	bool bAllowRotation = false;

	UPROPERTY(EditAnywhere, Category = "Custom Rotation")
	float RotationSpeed = 200.f;

	void RotateActor(float DeltaTime);
public:	

};
