// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaPickup.h"
#include "SleedGuys/Character/SleedCharacter.h"
#include "SleedGuys/SleederComponents/BuffComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AStaminaPickup::AStaminaPickup()
{
	bReplicates = true;
	PickupEffectComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PickupEffectComponent"));
	PickupEffectComponent->SetupAttachment(RootComponent);
}

void AStaminaPickup::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	ASleedCharacter* SleedCharacter = Cast<ASleedCharacter>(OtherActor);
	if (SleedCharacter)
	{
		UBuffComponent* Buff = SleedCharacter->GetBuff();
		if (Buff)
		{
			Buff->AddStamina(StaminaRegenAmount, StaminaRegenTime, bRegenOverTime);
		}
	}

	Destroy();
}

void AStaminaPickup::Destroyed()
{
	if (PickupEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			PickupEffect,
			GetActorLocation(),
			GetActorRotation()
		);
	}
	Super::Destroyed();
}
