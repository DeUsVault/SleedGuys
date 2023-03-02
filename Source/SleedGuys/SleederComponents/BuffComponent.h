// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BuffComponent.generated.h"

class ASleedCharacter;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLEEDGUYS_API UBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuffComponent();
	friend class ASleedCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void AddStamina(float StaminaRegenAmount, float StaminaRegenTime, bool bRegenOverTime);

protected:
	virtual void BeginPlay() override;
	void StaminaRampUp(float DeltaTime);

private:
	UPROPERTY()
	ASleedCharacter* Character;

	bool bIsStaminaRegenerating = false;
	float StaminaRegeneratingRate = 0;
	float StaminaAmountToRegen = 0.f;

public:	

		
};
