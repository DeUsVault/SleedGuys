// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceSpell.h"
#include "SleedGuys/Character/SleedCharacter.h"

void AForceSpell::BindSpellTimerFinished()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Forceeee"));

    TArray<AActor*> Result;
    GetOverlappingActors(Result);
    if (Result.Num() > 0)
    {
        for (auto Actor : Result)
        {
            if (Actor && Actor->ActorHasTag(FName("SleedCharacter")))
            {
                ASleedCharacter* overlappingCharacter = Cast<ASleedCharacter>(Actor);
                if (overlappingCharacter)
                {
                    FVector impactPoint = GetActorLocation();

                    FVector forceDirection = overlappingCharacter->GetActorLocation() - impactPoint;
                    forceDirection.Normalize();

                    FVector LaunchPower = FVector(forceDirection.X * ForcePower, forceDirection.Y * ForcePower, 0.f);

                    overlappingCharacter->ChangeAirFrictionAndLunch(LaunchPower);
                }
            }
        }
    }

    Destroy();
}
