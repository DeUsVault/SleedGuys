// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceSpell.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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

    float forceStrength = 10000.f; // Set the strength of the force

    // Filter the overlapping actors to include only Pawns
    TArray<APawn*> overlappingPawns;
    for (AActor* overlappingActor : overlappingActors)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Fuck"));
        ACharacter* overlappingCharacter = Cast<ACharacter>(overlappingActor);
        if (overlappingCharacter)
        {
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("bbb"));
            FVector forceDirection = overlappingCharacter->GetActorLocation() - impactPoint;
            forceDirection.Normalize();

            UCharacterMovementComponent* MovementComponent = overlappingCharacter->GetCharacterMovement();
            
            MovementComponent->Launch(forceDirection * forceStrength);
        }
    }
}
