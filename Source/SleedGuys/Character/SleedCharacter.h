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
class ARopeSwing;
class UCableComponent;

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
	void RopeButtonPressed();

	// Stamina Functions
	void UpdateHUDStamina();

	// MovementMode change functions
	void ChangeAirFrictionAndLunch(FVector LaunchPower);
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastChangeAirFriction(float Friction);

	float GroundFriction = 8.f;
	float AirFriction = 0.f;

	// Stun mechanic functions
	void ChangeStunState(ECharacterStunState StunState);

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

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* RopeAction;

private:
	// Controller
	ASleedPlayerController* SleedPlayerController;

	// Camera
	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	// CharacterMovementComponent
	UCharacterMovementComponent* MovementComp;

	UPROPERTY(Replicated, VisibleAnywhere)
	UCableComponent* Cable;

	// Jump Logic
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float firstJumpHeight = 420.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float secondJumpHeight = 600.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float JumpCost = 20.f;

	UPROPERTY(Replicated)
	bool bShouldDoubleJump;

	// Weapon Logic
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_OverlappingWeapon)
	ABaseWeapon* OverlappingWeapon;

	UFUNCTION()
	void OnRep_OverlappingWeapon(ABaseWeapon* LastWeapon);

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	// CombatComponent
	UPROPERTY(VisibleAnywhere)
	UCombatComp* Combat;

	bool IsStunned();

	// BuffComponent 
	UPROPERTY(VisibleAnywhere)
	UBuffComponent* Buff;

	// Character Attributes
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

	UPROPERTY(ReplicatedUsing = OnRep_Gold, VisibleAnywhere, Category = "Player Stats")
	int32 Gold;

	UFUNCTION()
	void OnRep_Gold();

	void UpdateHUDGold();

	// Sprint Functions
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

	// Stun Functions
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_CharStunState, VisibleAnywhere, Category = "Stun")
	ECharacterStunState CharacterStunState = ECharacterStunState::ECS_Init;

	UPROPERTY(VisibleAnywhere, Category = "Stun")
	int32 ButtonPresses = 0;

	UFUNCTION(Server, Reliable)
	void ServerButtonPressed();

	UFUNCTION(Server, Reliable)
	void ServerChangeStunState(ECharacterStunState StunState);

	UFUNCTION(Client, Reliable)
	void ClientStunStateChanged(ECharacterStunState StunState);

	UFUNCTION()
	void OnRep_CharStunState();

	void HandleButtonPress();
	void StunWidgetVisibility(ECharacterStunState StunState = ECharacterStunState::ECS_Default);
	void UpdateStunButtonHUD(int32 num);

public:
	// Place for Getters/Setters only
	void SetOverlappingWeapon(ABaseWeapon* Weapon);
	bool IsWeaponEquipped();
	FORCEINLINE bool getShouldDoubleJump() { return this->bShouldDoubleJump; }
	FORCEINLINE UBuffComponent* GetBuff() const { return this->Buff; }
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE void SetStamina(float Amount) { Stamina = Amount; }
	void AddGold(int32 AmountOfGold);
	FORCEINLINE int32 GetGold() const { return this->Gold; }
	FORCEINLINE ECharacterStunState GetCharacterStunState() const { return this->CharacterStunState; }

	// Rope Logic
	void SetOverlappingRopeSwing(ARopeSwing* RopeSwing);
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_OverlappingRopeSwing)
	ARopeSwing* OverlappingRopeSwing;

	UFUNCTION()
	void OnRep_OverlappingRopeSwing(ARopeSwing* LastRopeSwing);

	UFUNCTION(Server, Reliable)
	void ServerCreateCable();

	UFUNCTION(Server, Reliable)
	void ServerBreakCable();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastUpdateCable(bool bBreak);

	void RopeSwing(float DeltaTime);

	void AddSwingRotation(FVector& Distance, float DeltaTime);

	UPROPERTY(Replicated)
	bool bIsRoping = false;

};
