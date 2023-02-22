// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CombatComponent.generated.h"

UCLASS()
class SLEEDGUYS_API ACombatComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	ACombatComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
