// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObstacleSphereOverlap.h"
#include "ObstacleSlide.generated.h"

class UNiagaraComponent;

UCLASS()
class SLEEDGUYS_API AObstacleSlide : public AObstacleSphereOverlap
{
	GENERATED_BODY()

public:
	AObstacleSlide();

protected:
	virtual void BeginPlay() override;

	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	) override;

	virtual void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	) override;

private:
	UPROPERTY(EditAnywhere)
	UNiagaraComponent* IceVisual;
};
