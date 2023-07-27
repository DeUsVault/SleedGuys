// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleOverlap.h"
#include "SleedGuys/Enums/DamageTypes.h"
#include "ObstacleDoubleOverlap.generated.h"

class UBoxComponent;
class UNiagaraSystem;
class UCustomDamageType;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AObstacleDoubleOverlap : public AObstacleOverlap
{
	GENERATED_BODY()

public:
	AObstacleDoubleOverlap();

	// bind overlap is called on the actor from another actor, for example from the ObstacleArray
	virtual void BindOverlap() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SecondObstacleMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SecondOverlapBox;

	UFUNCTION()
	virtual void OnSecondBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	virtual void OnBoxOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

	void HandleCharacterOverlap(AActor* OtherActor, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere)
	float DamageToApply = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<UCustomDamageType> DamageTypeClass;
};
