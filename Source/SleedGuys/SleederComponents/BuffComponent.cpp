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

	StaminaRampUp(DeltaTime);
}

void UBuffComponent::StaminaRampUp(float DeltaTime)
{
	if (!bIsStaminaRegenerating || Character == nullptr) return;

	const float RegenThisFrame = StaminaRegeneratingRate * DeltaTime;
	float AmountToRegen = FMath::Clamp(Character->GetStamina() + RegenThisFrame, 0.f, Character->GetMaxStamina());

	Character->SetStamina(AmountToRegen);
	Character->UpdateHUDStamina();
	StaminaAmountToRegen = StaminaAmountToRegen - RegenThisFrame;

	if (StaminaAmountToRegen <= 0.f || Character->GetStamina() >= Character->GetMaxStamina())
	{
		bIsStaminaRegenerating = false;
		StaminaAmountToRegen = 0.f;
	}
}

void UBuffComponent::AddStamina(float StaminaRegenAmount, float StaminaRegenTime, bool bRegenOverTime)
{
	if (bRegenOverTime)
	{	
		bIsStaminaRegenerating = true;
		StaminaRegeneratingRate = StaminaRegenAmount / StaminaRegenTime;
		StaminaAmountToRegen = StaminaAmountToRegen + StaminaRegenAmount;
	}
	else
	{
		float StaminaNum = FMath::Clamp(Character->GetStamina() + StaminaRegenAmount, 0.f, Character->GetMaxStamina());
		Character->SetStamina(StaminaNum);
		Character->UpdateHUDStamina(); // here it only happens if we have authority because on pickup class we set the overlapping functions to happen on authority only
	}
}

