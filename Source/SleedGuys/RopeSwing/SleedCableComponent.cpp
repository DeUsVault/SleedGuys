// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedCableComponent.h"

USleedCableComponent::USleedCableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
}

void USleedCableComponent::BeginPlay()
{
}

void USleedCableComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
