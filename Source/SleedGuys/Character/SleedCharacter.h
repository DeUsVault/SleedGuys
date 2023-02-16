// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SleedCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class SLEEDGUYS_API ASleedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASleedCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

public:
	// Place for Getters/Setters only

};
