// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CableComponent.h"
#include "SleedCableComponent.generated.h"

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API USleedCableComponent : public UCableComponent
{
	GENERATED_BODY()

public:
	USleedCableComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

};
