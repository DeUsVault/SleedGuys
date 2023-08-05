// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrownProjectile.h"
#include "Components/SphereComponent.h"
#include "SleedGuys/CheckpointTrigger.h"
#include "SleedGuys/Character/SleedCharacter.h"

AThrownProjectile::AThrownProjectile()
{
	bReplicates = false;

	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
}

void AThrownProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AThrownProjectile::CheckDestruction, DestroyCheckRate, true);
}

void AThrownProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		ACheckpointTrigger* CheckpointActor = Cast<ACheckpointTrigger>(OtherActor);
		if (CheckpointActor)
		{	
			AActor* OwnerActor = GetOwner();
			ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OwnerActor);
			if (SleedCharacter)
			{
				CheckpointActor->GotHitted(SleedCharacter);
			}
		}
	}
}

void AThrownProjectile::CheckDestruction()
{
	if (!IsValid(this)) return;

	DestructionNumChecks++;
	if (DestructionNumChecks > 1)
	{
		Destroy();
	}
}
