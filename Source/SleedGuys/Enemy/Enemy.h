// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SleedGuys/Enums/CharacterEnums.h"
#include "Enemy.generated.h"

class AAIController;
class UPawnSensingComponent;

UCLASS()
class SLEEDGUYS_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void CheckCombatTarget();
	void CheckPatrolTarget();
	virtual void Attack();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	AAIController* EnemyController;

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;

	UPROPERTY(BlueprintReadOnly, Replicated)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	/**
	* Ai logic - Navigation
	*/
	FTimerHandle PatrolTimer;
	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();

	UFUNCTION()
	virtual void PawnSeen(APawn* SeenPawn);

	/**
	* Combat logic
	*/
	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ChasingSpeed = 300.f;

private:
	/**
	* Navigation
	*/
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget; // Current patrol target

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 10.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolSpeed = 150.f;

	/**
	* Combat logic
	*/
	UPROPERTY(EditAnywhere, Category = "Combat")
	double CombatRadius = 800.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double AttackRadius = 300.f;

	/*
	* Components
	*/
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

public:	

};
