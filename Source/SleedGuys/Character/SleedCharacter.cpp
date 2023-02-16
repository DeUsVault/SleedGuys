// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ASleedCharacter::ASleedCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

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

