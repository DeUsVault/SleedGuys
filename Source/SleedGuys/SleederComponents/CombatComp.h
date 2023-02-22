// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComp.generated.h"

class ABaseWeapon;
class ASleedCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLEEDGUYS_API UCombatComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComp();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	friend class ASleedCharacter;

	void EquipWeapon(ABaseWeapon* WeaponToEquip);

protected:
	virtual void BeginPlay() override;

private:
	ASleedCharacter* Character;
	ABaseWeapon* EquippedWeapon;

public:	

		
};
