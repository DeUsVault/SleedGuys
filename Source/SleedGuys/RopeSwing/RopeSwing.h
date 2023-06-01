// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RopeSwing.generated.h"

class USphereComponent;
class UWidgetComponent;
class ASleedCharacter;
class UCableComponent;

UCLASS()
class SLEEDGUYS_API ARopeSwing : public AActor
{
	GENERATED_BODY()
	
public:	
	ARopeSwing();
	virtual void Tick(float DeltaTime) override;

	void ShowPickupWidget(bool bShowWidget);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);

	UFUNCTION()
	void OnSphereEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
	);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* AreaSphere;

	UPROPERTY(VisibleAnywhere, Category = "Swing Widget")
	UWidgetComponent* RopeSwingWidget;

	UPROPERTY(VisibleAnywhere)
	UCableComponent* Cable;

};
