// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "StaminaPickup.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AStaminaPickup : public APickup
{
	GENERATED_BODY()

public:
	AStaminaPickup();
	virtual void Destroyed() override;

protected:
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

private:

	UPROPERTY(EditAnywhere)
	float StaminaRegenAmount = 50.f;

	UPROPERTY(EditAnywhere)
	float StaminaRegenTime = 4.f;

	UPROPERTY(EditAnywhere)
	bool bRegenOverTime = false;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* PickupEffectComponent;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupEffect;
	
};
