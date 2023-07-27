// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingObstacleTurret.h"
#include "Particles/ParticleSystemComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "Kismet/GameplayStatics.h"

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
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("hit"));
		UGameplayStatics::ApplyDamage(SleedCharacter, DamagePerSecond, nullptr, this, UDamageType::StaticClass());

		bCanApplyDamage = false;
	}
}

void AMovingObstacleTurret::ResetDamageCooldown()
{
	// Allow damage to be applied again
	bCanApplyDamage = true;
}
