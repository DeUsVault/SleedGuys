// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class USoundCue;

UCLASS()
class SLEEDGUYS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	virtual void Destroyed() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	USphereComponent* OverlapSphere;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* CollisionEffect = nullptr;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* ContinuousEffect = nullptr;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DestructionEffect = nullptr;

	void playNiagaraEffect(UNiagaraSystem* Effect);

	UPROPERTY(EditAnywhere)
	USoundCue* HitSound;

	void playSoundEffect(USoundCue* Sound);

private:	
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float InitMoveSpeed = 2500.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxMoveSpeed = 2500.f;

	FTimerHandle BindOverlapTimer;
	float BindOverlapTime = 0.1f;
	virtual void BindOverlapTimerFinished();

};
