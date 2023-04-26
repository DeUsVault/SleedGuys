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
	if (OtherActor)
	{
		ASleedCharacter* HittedCharacter = Cast<ASleedCharacter>(OtherActor);
		if (HittedCharacter)
		{	
			if (HasAuthority())
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("authority overlap"));
			}
			HittedCharacter->ChangeStunState(ECharacterStunState::ECS_Xstun);
			Destroy();
		}
	}
}

void AStunProjectile::CheckDestruction()
{
	DestructionNumChecks++;

	if (DestructionNumChecks > 1)
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
		Destroy();
	}
}
