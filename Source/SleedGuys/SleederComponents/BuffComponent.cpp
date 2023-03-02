// Fill out your copyright notice in the Description page of Project Settings.


#include "BuffComponent.h"
#include "SleedGuys/Character/SleedCharacter.h"

UBuffComponent::UBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UBuffComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UBuffComponent::AddStamina(float StaminaRegenAmount, float StaminaRegenTime, bool bRegenOverTime)
{
	if (!bRegenOverTime)
	{	
		float StaminaNum = FMath::Clamp(Character->GetStamina() + StaminaRegenAmount, 0.f, Character->GetMaxStamina());
		Character->SetStamina(StaminaNum);
		Character->UpdateHUDStamina(); // here it only happens if we have authority because on pickup class we set the overlapping functions to happen on authority only
	}
	else
	{

	}
}

