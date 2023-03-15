// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellcasterEnemy.h"
#include "AIController.h"
#include "SleedGuys/Spells/Spell.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SleedGuys/Enums/CharacterEnums.h"

void ASpellcasterEnemy::Tick(float DeltaTime)
{
	ACharacter::Tick(DeltaTime); // call the 'default' tick function first

	if (EnemyState == EEnemyState::EES_Spellcasting) return; // we dont want enemy to do anything else

	if (EnemyState > EEnemyState::EES_Patrolling)
	{
		CheckCombatTarget();
	}
	else
	{
		CheckPatrolTarget();
	}
}

void ASpellcasterEnemy::PawnSeen(APawn* SeenPawn)
{
	if (EnemyState != EEnemyState::EES_Chasing
		&& EnemyState != EEnemyState::EES_Attacking
		&& EnemyState != EEnemyState::EES_Spellcasting
		&& SeenPawn->ActorHasTag(FName("SleedCharacter")))
	{
		CombatTarget = SeenPawn;
		GetWorldTimerManager().ClearTimer(PatrolTimer);
		GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;
		EnemyState = EEnemyState::EES_Chasing;
		MoveToTarget(CombatTarget);
	}
}

void ASpellcasterEnemy::Attack()
{
	if (CurrentSpell != nullptr) return;

	if (Spell)
	{
		EnemyState = EEnemyState::EES_Spellcasting;
		EnemyController->StopMovement();
		CurrentSpell = GetWorld()->SpawnActor<ASpell>(Spell, GetActorTransform());
		CurrentSpell->setSpellCaster(this);
	}
}
