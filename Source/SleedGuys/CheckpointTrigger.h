// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CheckpointTrigger.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class ASleedCharacter;
class APlayerStart;
class UNiagaraSystem;
class UTextRenderComponent;

UCLASS()
class SLEEDGUYS_API ACheckpointTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ACheckpointTrigger();
	virtual void Destroyed() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	void GotHitted(ASleedCharacter* Character);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	USphereComponent* CheckpointTriggerSphere;

	UPROPERTY(EditInstanceOnly)
	APlayerStart* CheckpointPlayerStart;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* DestructionEffect;

private:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CheckpointMesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* CheckpointMovementComponent;

	// trigger sphere overlap function
	FTimerHandle BindOverlapTimer;
	float BindOverlapTime = 0.1f;
	virtual void BindOverlapTimerFinished();

	UPROPERTY(EditAnywhere)
	FVector MoveDirection = FVector(0.f, 0.f, 1.f);

	UPROPERTY(EditAnywhere)
	float DesiredSpeed = 150.f;

	// trigger destroy function
	FTimerHandle DestroyTimer;
	UPROPERTY(EditAnywhere)
	float DestroyTime = 20.f;
	virtual void BindDestroyTimerFinished();

	// text
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* Text;

};
