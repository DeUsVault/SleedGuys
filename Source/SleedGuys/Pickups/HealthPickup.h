// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "HealthPickup.generated.h"

class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AHealthPickup : public APickup
{
	GENERATED_BODY()

public:
	AHealthPickup();
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
	float HealthRegenAmount = 50.f;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* PickupEffectComponent;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* PickupEffect;
	
};
