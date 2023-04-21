// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceProjectile.h"
#include "Components/SphereComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"

AForceProjectile::AForceProjectile()
{	
	bReplicates = true;
}

void AForceProjectile::BeginPlay()
{	
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AForceProjectile::CheckDestruction, DestroyCheckRate, true);
}

void AForceProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	float Speed = this->GetVelocity().Size();
	if (Speed <= MinVelocityOverlapTrigger)
	{
		// disable overlap events if speed is too low
		OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &AProjectile::OnSphereOverlap);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(Speed));
		return;
	}

	if (OtherActor)
	{
		ASleedCharacter* HittedCharacter = Cast<ASleedCharacter>(OtherActor);
		if (HittedCharacter)
		{
			FVector impactPoint = GetActorLocation();
			FVector forceDirection = HittedCharacter->GetActorLocation() - impactPoint;
			forceDirection.Normalize();

			FVector LaunchPower = FVector(forceDirection.X * ForcePower, forceDirection.Y * ForcePower, 0.f);

			HittedCharacter->ChangeAirFrictionAndLunch(LaunchPower);

			// disable overlap events, we want the projectile to interact only one time
			OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &AProjectile::OnSphereOverlap);
		}
	}
}

void AForceProjectile::CheckDestruction()
{	
	DestructionNumChecks++;

	float Speed = this->GetVelocity().Size();
	if (Speed <= MinVelocityDestroyTrigger || DestructionNumChecks > 1)
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		Destroy();
	}
}
