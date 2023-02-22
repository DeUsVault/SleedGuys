// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

ACombatComponent::ACombatComponent()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

