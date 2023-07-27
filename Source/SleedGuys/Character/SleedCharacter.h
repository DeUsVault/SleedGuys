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
class ASleedPlayerState;
class ARopeSwing;
class USleedCableComponent;
class UNiagaraSystem;

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
	void Celebrate();
	void GameMenu();

	// Stamina Functions
	void UpdateHUDStamina();

	// Health Functions
	void UpdateHUDHealth();

	// MovementMode change functions
	void ChangeAirFrictionAndLunch(FVector LaunchPower);
	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastChangeAirFriction(float Friction);

	float GroundFriction = 8.f;
	float AirFriction = 0.f;

	// Stun mechanic functions
	void ChangeStunState(ECharacterStunState StunState);

	// rope swing
	void SetOverlappingRopeSwing(ARopeSwing* RopeSwing);

	// Slide Functions
	void setIsSliding(bool bSlides);

	// Death logic
	void Elim();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastElim();

	void PlayElimMontage();

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

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Celebration;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* GameMenuCall;

	// Damage - Health
	UFUNCTION()
	void ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatorController, AActor* DamageCauser);

	UPROPERTY(EditAnywhere, Category = Combat)
	UAnimMontage* ElimMontage;

private:
	// Controller
	ASleedPlayerController* SleedPlayerController;

	// Player State
	ASleedPlayerState* SleedPlayerState;

	// Camera
	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* FollowCamera;

	// CharacterMovementComponent
	UCharacterMovementComponent* MovementComp;

	UPROPERTY(Replicated, VisibleAnywhere)
	USleedCableComponent* Cable;

	// Jump Logic
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float firstJumpHeight = 420.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float secondJumpHeight = 600.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float swingJumpHeight = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float JumpCost = 20.f;

	UPROPERTY(Replicated)
	EJumpState JumpState = EJumpState::EJS_NoJump;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* FirstJumpEffect = nullptr;

	UPROPERTY(EditAnywhere)
	UNiagaraSystem* SecondaryJumpEffect = nullptr;

	void NiagaraJumpEffect(UNiagaraSystem* JumpEffect);

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

	bool IsAlive();

	UPROPERTY(EditAnywhere, Category = "Player Stats")
	float MaxStamina = 100.f;

	UPROPERTY(ReplicatedUsing = OnRep_Stamina, EditAnywhere, Category = "Player Stats")
	float Stamina = 100.f;

	UFUNCTION()
	void OnRep_Stamina();

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

	//
	// Rope Swing
	//
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

	FVector RopeSwingLocation;

	void BreakSwing();

	UPROPERTY(Replicated)
	bool bIsCelebrating = false;

	// slide
	void Slide();
	float ForwardSlide = 0.f;
	float RightSlide = 0.f;

	UPROPERTY(EditAnywhere, Category = "Sliding")
	float MinSlidePower = -3.f;

	UPROPERTY(EditAnywhere, Category = "Sliding")
	float MaxSlidePower = 3.f;

	UPROPERTY(EditAnywhere, Category = "Sliding")
	float InitialSlidePower = 1.f;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_IsSliding)
	bool bIsSliding = false;

	UFUNCTION()
	void OnRep_IsSliding();

	// elimination
	bool bElimmed = false;

	FTimerHandle ElimTimer;

	UPROPERTY(EditDefaultsOnly)
	float ElimDelay = 3.f;

	void ElimTimerFinished();

public:
	// Place for Getters/Setters only
	void SetOverlappingWeapon(ABaseWeapon* Weapon);
	bool IsWeaponEquipped();
	FORCEINLINE EJumpState getJumpState() { return this->JumpState; }
	FORCEINLINE UBuffComponent* GetBuff() const { return this->Buff; }
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	FORCEINLINE void SetStamina(float Amount) { Stamina = Amount; }
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	FORCEINLINE void SetHealth(float Amount) { Health = Amount; }
	void AddGold(int32 AmountOfGold);
	FORCEINLINE ECharacterStunState GetCharacterStunState() const { return this->CharacterStunState; }
	FORCEINLINE bool IsCelebrating() const { return this->bIsCelebrating; }
	FORCEINLINE bool GetIsSliding() const { return this->bIsSliding; }
	FORCEINLINE bool IsElimmed() const { return bElimmed; }
};
