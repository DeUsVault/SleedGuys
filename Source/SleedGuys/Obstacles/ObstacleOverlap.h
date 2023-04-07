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
/*
void AHammerActor::OnCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        FVector impactPoint = Hit.ImpactPoint;
        float radius = 500.0f; // Set the radius of the search

        // Create a sphere with the specified radius and location
        FCollisionShape collisionShape = FCollisionShape::MakeSphere(radius);

        // Set up the query parameters to include only Pawns
        FCollisionQueryParams queryParams;
        queryParams.AddIgnoredActor(this);
        queryParams.bTraceComplex = true;
        queryParams.bReturnPhysicalMaterial = false;
        queryParams.AddIgnoredActor(GetOwner());
        queryParams.bTraceAsyncScene = true;
        queryParams.bReturnFaceIndex = false;
        queryParams.bIgnoreBlocks = false;
        queryParams.bIgnoreTouches = false;
        queryParams.bIgnoreTouchesUnderneath = false;
        queryParams.bOnlyCollidingComponents = false;

        // Use the collision shape and query parameters to get all overlapping actors
        TArray<AActor*> overlappingActors;
        GetWorld()->OverlapMultiByObjectType(
            overlappingActors,
            impactPoint,
            FQuat::Identity,
            FCollisionObjectQueryParams(ECC_Pawn),
            collisionShape,
            queryParams
        );

        // Filter the overlapping actors to include only Pawns
        TArray<APawn*> overlappingPawns;
        for (AActor* overlappingActor : overlappingActors)
        {
            APawn* overlappingPawn = Cast<APawn>(overlappingActor);
            if (overlappingPawn)
            {
                overlappingPawns.Add(overlappingPawn);
            }
        }

        // Apply a force to all overlapping Pawns
        float forceStrength = 1000.0f; // Set the strength of the force
        for (APawn* overlappingPawn : overlappingPawns)
        {
            FVector forceDirection = overlappingPawn->GetActorLocation() - impactPoint;
            forceDirection.Normalize();
            overlappingPawn->GetMovementComponent()->AddForce(forceDirection * forceStrength, NAME_None, true);
        }
    }
}
*/