// Fill out your copyright notice in the Description page of Project Settings.


#include "StunProjectile.h"
#include "Components/SphereComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "SleedGuys/Enums/CharacterEnums.h"

AStunProjectile::AStunProjectile()
{
	bReplicates = true;
}

void AStunProjectile::BeginPlay()
{	
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &AStunProjectile::CheckDestruction, DestroyCheckRate, true);
}

void AStunProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (!IsValid(this)) return;

	if (OtherActor)
	{
		ASleedCharacter* HittedCharacter = Cast<ASleedCharacter>(OtherActor);
		if (HittedCharacter)
		{	
			OverlapSphere->OnComponentBeginOverlap.RemoveDynamic(this, &AStunProjectile::OnSphereOverlap);
			HittedCharacter->ChangeStunState(ECharacterStunState::ECS_Xstun);

			playNiagaraEffect(CollisionEffect);

			if (IsValid(this))
			{	
				GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
				Destroy();
			}
		}
	}
}

void AStunProjectile::CheckDestruction()
{	
	if (!IsValid(this)) return;

	DestructionNumChecks++;

	if (DestructionNumChecks > 1)
	{	
		Destroy();
	}
}
