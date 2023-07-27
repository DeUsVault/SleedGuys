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
	if (!IsValid(this)) return;

	float Speed = this->GetVelocity().Size();
	if (Speed <= MinVelocityOverlapTrigger)
	{
		// disable overlap events if speed is too low
		OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &AForceProjectile::OnSphereOverlap);
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

			// disable overlap events, we want the projectile to interact only one time
			OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &AForceProjectile::OnSphereOverlap);

			HittedCharacter->ChangeAirFrictionAndLunch(LaunchPower);

			playNiagaraEffect(CollisionEffect);

			if (IsValid(this))
			{
				GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
				Destroy();
			}
		}
	}
}

void AForceProjectile::CheckDestruction()
{	
	if (!IsValid(this)) return;

	DestructionNumChecks++;

	float Speed = this->GetVelocity().Size();
	if (Speed <= MinVelocityDestroyTrigger || DestructionNumChecks > 1)
	{	
		Destroy();
	}
}
