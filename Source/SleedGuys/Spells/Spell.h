// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class SLEEDGUYS_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpell();
	virtual void Tick(float DeltaTime) override;

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

private:
	UPROPERTY(EditAnywhere)
	USphereComponent* OverlapSphere;

	UPROPERTY(VisibleAnywhere)
	UNiagaraComponent* SpellEffectComponent;

	UPROPERTY(EditAnywhere)
	float SpellSphereRadius = 300.f;

	FTimerHandle BindSpellTimer;
	virtual void BindSpellTimerFinished();

	UPROPERTY(EditAnywhere)
	float BindSpellTime = 3.f;

	UPROPERTY(VisibleAnywhere)
	AActor* SpellCaster;

public:
	// getters
	// and
	// setters
	void setSpellCaster(AActor* Caster);

};
