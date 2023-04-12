// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spell.h"
#include "ForceSpell.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API AForceSpell : public ASpell
{
	GENERATED_BODY()

private:
	virtual void BindSpellTimerFinished() override;

	UPROPERTY(EditAnywhere, Category = "Custom Force")
	float ForcePower = 10000.f;
};
