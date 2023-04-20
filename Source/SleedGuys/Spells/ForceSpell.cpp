// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceSpell.h"
#include "SleedGuys/Character/SleedCharacter.h"

void AForceSpell::BindSpellTimerFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Forceeee"));
    FVector impactPoint = GetActorLocation();
    float radius = 500.0f; // Set the radius of the search

    // Create a sphere with the specified radius and location
    FCollisionShape collisionShape = FCollisionShape::MakeSphere(radius);

    // Set up the query parameters to include only Pawns
    FCollisionQueryParams queryParams;
    queryParams.AddIgnoredActor(this);
    queryParams.bTraceComplex = true;
    queryParams.bReturnPhysicalMaterial = false;
    queryParams.AddIgnoredActor(GetOwner());
    queryParams.bReturnFaceIndex = false;
    queryParams.bIgnoreBlocks = false;
    queryParams.bIgnoreTouches = false;

    // Use the collision shape and query parameters to get all overlapping actors
    TArray<FOverlapResult> overlappingResults;
    GetWorld()->OverlapMultiByObjectType(
        overlappingResults,
        impactPoint,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECC_Pawn),
        collisionShape,
        queryParams
    );

    TArray<AActor*> overlappingActors;
    for (const FOverlapResult& overlap : overlappingResults)
    {
        AActor* overlappingActor = overlap.GetActor();
        if (overlappingActor && overlappingActor->IsA<APawn>())
        {
            overlappingActors.Add(overlappingActor);
        }
    }

    // Filter the overlapping actors to include only Pawns
    TArray<APawn*> overlappingPawns;
    for (AActor* overlappingActor : overlappingActors)
    {
        ASleedCharacter* overlappingCharacter = Cast<ASleedCharacter>(overlappingActor);
        if (overlappingCharacter)
        {
            FVector forceDirection = overlappingCharacter->GetActorLocation() - impactPoint;
            forceDirection.Normalize();

            FVector LaunchPower = FVector(forceDirection.X * ForcePower, forceDirection.Y * ForcePower, 0.f);

            overlappingCharacter->ChangeAirFrictionAndLunch(LaunchPower);
        }

    }
}
