// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComp.generated.h"

class ABaseWeapon;
class ASleedCharacter;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLEEDGUYS_API UCombatComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComp();
	friend class ASleedCharacter;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void EquipWeapon(ABaseWeapon* WeaponToEquip);

protected:
	virtual void BeginPlay() override;


	UFUNCTION(Server, Reliable)
	void ServerStartThrow();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastThrow();

	UFUNCTION(Server, Reliable)
	void ServerThrow(FVector Location, FRotator Rotation);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastThrowProjectile(FVector Location, FRotator Rotation);

	UPROPERTY(EditAnywhere)
	TSubclassOf<AProjectile> ProjectileClass;

private:
	ASleedCharacter* Character;

	UPROPERTY(Replicated)
	ABaseWeapon* EquippedWeapon;

	// throw
	UPROPERTY(EditAnywhere, Category = "Throwing")
	float ThrowPitchOffset = 20.f;

public:	

		
};
