// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "SleedGuys/Enums/DamageTypes.h"
#include "CustomDamageType.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API UCustomDamageType : public UDamageType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	EDamageTypes CustomDamageType = EDamageTypes::EDT_Simple;
	
};
