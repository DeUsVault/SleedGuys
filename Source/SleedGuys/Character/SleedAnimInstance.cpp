// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedAnimInstance.h"
#include "SleedCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

void USleedAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SleedCharacter = Cast<ASleedCharacter>(TryGetPawnOwner());
}

void USleedAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (SleedCharacter == nullptr)
	{
		SleedCharacter = Cast<ASleedCharacter>(TryGetPawnOwner());
	}
	if (SleedCharacter == nullptr) return;

	FVector Velocity = SleedCharacter->GetVelocity();
	Velocity.Z = 0.f;
	Speed = Velocity.Size();

	bIsInAir = SleedCharacter->GetCharacterMovement()->IsFalling();
	JumpState = SleedCharacter->getJumpState();
	bIsAccelerating = SleedCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
	bWeaponEquipped = SleedCharacter->IsWeaponEquipped();
	CharStunState = SleedCharacter->GetCharacterStunState();
	bSliding = SleedCharacter->GetIsSliding();
	bCelebrates = SleedCharacter->IsCelebrating();
	bElimmed = SleedCharacter->IsElimmed();
}

