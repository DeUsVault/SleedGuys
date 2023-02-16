// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedCharacter.h"

ASleedCharacter::ASleedCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ASleedCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASleedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASleedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

