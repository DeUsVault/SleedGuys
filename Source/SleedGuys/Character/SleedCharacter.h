// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SleedGuys/Enums/CharacterEnums.h"
#include "SleedCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class ABaseWeapon;
class UCombatComp;
class UBuffComponent;
class ASleedPlayerController;

UCLASS()
class SLEEDGUYS_API ASleedCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASleedCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual void Landed(const FHitResult& Hit) override;

	/* 
	*	Callbacks for input 
	*/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	void EquipButtonPressed();
	void Sprint();
	void XButtonPressed();

	// Stamina Functions
	//
	//
	void UpdateHUDStamina();

	//
	// movement mode change functions
	//
	void ChangeAirFrictionAndLunch(FVector LaunchPower);
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastChangeAirFriction(float Friction);

	float GroundFriction = 8.f;
	float AirFriction = 0.f;

	//
	// stun mechanic functions
	//
	void ChangeStunState(ECharacterStunState StunState);

	UFUNCTION(Server, Reliable)
	void ServerChangeStunState(ECharacterStunState StunState);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* SleedContext;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EquipAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* XButtonAction;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_CharStunState, VisibleAnywhere, Category = "Stun")
	ECharacterStunState CharacterStunState = ECharacterStunState::ECS_Init;

	UFUNCTION()
	void OnRep_CharStunState();

	UFUNCTION(Client, Reliable)
	void ClientStunStateChanged(ECharacterStunState StunState);

	void StunWidgetVisibility(ECharacterStunState StunState = ECharacterStunState::ECS_Default);

	UFUNCTION(Server, Reliable)
	void ServerButtonPressed();

	UPROPERTY(VisibleAnywhere, Category = "Stun")
	int32 ButtonPresses = 0;

	void HandleButtonPress();

	void UpdateStunButtonHUD(int32 num);

private:
	// Controller
	//
	//

	ASleedPlayerController* SleedPlayerController;

	// Camera
	//
	//
	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	//
	// character movement component
	//
	UCharacterMovementComponent* MovementComp;

	// Jump Logic
	//
	//
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float firstJumpHeight = 420.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float secondJumpHeight = 600.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float JumpCost = 20.f;

	UPROPERTY(Replicated)
	bool bShouldDoubleJump;

	// Weapon Logic
	//
	//
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_OverlappingWeapon)
	ABaseWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(ABaseWeapon* LastWeapon);

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	// Combat Logic
	//
	//
	UPROPERTY(VisibleAnywhere)
	UCombatComp* Combat;

	// Buff Component logic
	//
	//
	UPROPERTY(VisibleAnywhere)
	UBuffComponent* Buff;

	// Character Attributes
	//
	//
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxHealth = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Health, EditAnywhere, Category = "Player Stats")
	float Health = 100.f;

	UFUNCTION()
	void OnRep_Health();

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxStamina = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Stamina, EditAnywhere, Category = "Player Stats")
	float Stamina = 100.f;

	UFUNCTION()
	void OnRep_Stamina();

	// Sprint 
	//
	//
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float OriginalSpeed = 600.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float SprintSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float SprintCost = 25.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxSprintTime = 5.f;

	FTimerHandle SprintTimer;

	void SprintTimerFinished();

	UFUNCTION(Server, Reliable)
	void ServerSprint(float Speed, bool breduceStamina);

	//
	// Coins
	//
	UPROPERTY(ReplicatedUsing = OnRep_Gold, VisibleAnywhere, Category = "Resources")
	int32 Gold;

	UFUNCTION()
	void OnRep_Gold();

	void UpdateHUDGold();

	//
	// stun
	//
	bool IsStunned();
public:
	// Place for Getters/Setters only
	//
	//
	void SetOverlappingWeapon(ABaseWeapon* Weapon);
	FORCEINLINE bool getShouldDoubleJump() { return this->bShouldDoubleJump; }
	bool IsWeaponEquipped();
	FORCEINLINE UBuffComponent* GetBuff() const { return this->Buff; }
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE void SetStamina(float Amount) { Stamina = Amount; }
	void AddGold(int32 AmountOfGold);
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE ECharacterStunState GetCharacterStunState() const { return CharacterStunState; }

};
