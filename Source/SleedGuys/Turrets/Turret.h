// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

class UBoxComponent;
class AProjectile;

UCLASS()
class SLEEDGUYS_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();
	virtual void Tick(float DeltaTime) override;

	void Fire();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AProjectile>> ProjectileClasses;

	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> PossibleTargets;

private:	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* ProjectileSpawnPoint;

	FTimerHandle FireRateTimerHandle;

	UPROPERTY(EditAnywhere, Category = "Fire Events")
	float FireRateMin = 2.f;

	UPROPERTY(EditAnywhere, Category = "Fire Events")
	float FireRateMax = 3.f;

	float RandomFireRate = 2.5;

	FVector ProjectileSpawnPointLocation;

	UPROPERTY(EditAnywhere, Category = "Fire Events")
	float RandomHitTargetOffset = 100.f;

	UPROPERTY(EditAnywhere, Category = "Fire Events")
	bool bUseRandomOffset = false;

};
