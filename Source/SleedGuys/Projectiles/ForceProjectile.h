// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "ForceProjectile.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AForceProjectile : public AProjectile
{
	GENERATED_BODY()

public:
	AForceProjectile();

	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

	void CheckDestruction();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	float ForcePower = 10000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MinVelocityOverlapTrigger = 500.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MinVelocityDestroyTrigger = 250.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DestroyCheckRate = 5.f;

	int32 DestructionNumChecks = 0;

	FTimerHandle DestroyTimerHandle;
	
};
