// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacleTurret.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

AMovingObstacleTurret::AMovingObstacleTurret()
{	
}

void AMovingObstacleTurret::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(DamageCooldownTimerHandle, this, &AMovingObstacleTurret::ResetDamageCooldown, DamageCooldownDuration, true);
}

void AMovingObstacleTurret::ActorOverlap(AActor* Actor)
{	
	if (!bCanApplyDamage) return;

	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(Actor);
	if (SleedCharacter)
	{	
		if (SleedCharacter->IsElimmed()) return; // do not apply damage to already dead character
		UGameplayStatics::ApplyDamage(SleedCharacter, DamagePerSecond, nullptr, this, UDamageType::StaticClass());

		bCanApplyDamage = false;

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				SleedCharacter->GetActorLocation()
			);
		}
	}
}

void AMovingObstacleTurret::ResetDamageCooldown()
{
	// Allow damage to be applied again
	bCanApplyDamage = true;
}
