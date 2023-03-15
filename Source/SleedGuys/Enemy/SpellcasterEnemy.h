// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "SpellcasterEnemy.generated.h"

class ASpell;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API ASpellcasterEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Attack() override;

protected:
	/**
	* Spells
	*/
	UPROPERTY(EditAnywhere)
	TSubclassOf<ASpell> Spell; // set the spell from blueprint

	UPROPERTY()
	ASpell* CurrentSpell; // store the spell to this variable

	virtual void PawnSeen(APawn* SeenPawn) override;
	
};
