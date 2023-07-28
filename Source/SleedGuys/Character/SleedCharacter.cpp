// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "SleedGuys/Weapon/BaseWeapon.h"
#include "SleedGuys/RopeSwing/RopeSwing.h"
#include "SleedGuys/SleederComponents/CombatComp.h"
#include "SleedGuys/SleederComponents/BuffComponent.h"
#include "SleedGuys/RopeSwing/SleedCableComponent.h"
#include "SleedGuys/PlayerController/SleedPlayerController.h"
#include "SleedGuys/GameMode/SleedGameMode.h"
#include "SleedGuys/PlayerStates/SleedPlayerState.h"
#include "Kismet/KismetSystemLibrary.h"

#include "NiagaraFunctionLibrary.h"
#include "Components/CapsuleComponent.h"

#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

ASleedCharacter::ASleedCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	GetMesh()->SetGenerateOverlapEvents(true);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	// CameraBoom - we must also set from blueprint - use pawn control rotation to true - that way we cant change rotation of camera though!!

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	FollowCamera->SetupAttachment(CameraBoom);

	Combat = CreateDefaultSubobject<UCombatComp>(TEXT("CombatComponent"));
	Combat->SetIsReplicated(true);

	Buff = CreateDefaultSubobject<UBuffComponent>(TEXT("BuffComponent"));
	Buff->SetIsReplicated(true);

	Cable = CreateDefaultSubobject<USleedCableComponent>(TEXT("CableComponent"));
	Cable->SetupAttachment(GetRootComponent());
	Cable->SetIsReplicated(true);
}

void ASleedCharacter::BeginPlay()
{
	Super::BeginPlay();

	SleedPlayerController = Cast<ASleedPlayerController>(Controller);
	if (SleedPlayerController)
	{	
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(SleedPlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(SleedContext, 0);
		}

		if (HasAuthority())
		{
			OnTakeAnyDamage.AddDynamic(this, &ASleedCharacter::ReceiveDamage);
		}

		SleedPlayerController->SetHUDHealth(Health, MaxHealth);
		SleedPlayerController->SetHUDStamina(Stamina, MaxStamina);
	}

	MovementComp = GetCharacterMovement();
	if (MovementComp)
	{
		GroundFriction = MovementComp->GroundFriction;
		AirFriction = MovementComp->FallingLateralFriction;
	}

	if (Cable)
	{	
		Cable->SetVisibility(false);
		Cable->SetActive(false);
	}

	Tags.Add(FName("SleedCharacter"));
}

void ASleedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementComp)
	{
		FHitResult OutHit;
		MovementComp->SafeMoveUpdatedComponent(FVector(0.f, 0.f, 0.01f), GetActorRotation(), true, OutHit);
		MovementComp->SafeMoveUpdatedComponent(FVector(0.f, 0.f, -0.01f), GetActorRotation(), true, OutHit);
	}

	if (JumpState == EJumpState::EJS_Swinging)
	{
		RopeSwing(DeltaTime);
	}

	if (bIsSliding)
	{
		Slide();
	}

	/* way to check timerhandle
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("World delta for current frame equals %f"), GetWorldTimerManager().GetTimerElapsed(SprintTimer)));
	*/
}

void ASleedCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASleedCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASleedCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASleedCharacter::Jump);
		EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ASleedCharacter::EquipButtonPressed);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ASleedCharacter::Sprint);
		EnhancedInputComponent->BindAction(GameMenuCall, ETriggerEvent::Triggered, this, &ASleedCharacter::GameMenu);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ASleedCharacter::AimTrigger);

		// not used ingame atm
		EnhancedInputComponent->BindAction(RopeAction, ETriggerEvent::Triggered, this, &ASleedCharacter::RopeButtonPressed);
		EnhancedInputComponent->BindAction(XButtonAction, ETriggerEvent::Triggered, this, &ASleedCharacter::XButtonPressed);
		EnhancedInputComponent->BindAction(Celebration, ETriggerEvent::Triggered, this, &ASleedCharacter::Celebrate);
	}
}

void ASleedCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASleedCharacter, OverlappingWeapon, COND_OwnerOnly);
	DOREPLIFETIME(ASleedCharacter, JumpState);
	DOREPLIFETIME(ASleedCharacter, Health);
	DOREPLIFETIME(ASleedCharacter, Stamina);
	DOREPLIFETIME(ASleedCharacter, CharacterStunState);
	DOREPLIFETIME(ASleedCharacter, OverlappingRopeSwing);
	DOREPLIFETIME(ASleedCharacter, Cable); 
	DOREPLIFETIME(ASleedCharacter, bIsCelebrating);
	DOREPLIFETIME(ASleedCharacter, bIsSliding);
}

void ASleedCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	if (Combat)
	{
		Combat->Character = this;
	}
	if (Buff)
	{
		Buff->Character = this;
	}
}

void ASleedCharacter::ReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatorController, AActor* DamageCauser)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	UpdateHUDHealth();

	if(!IsAlive())
	{
		ASleedGameMode* SleedGameMode = GetWorld()->GetAuthGameMode<ASleedGameMode>();
		if (SleedGameMode && Controller)
		{	
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("sleed game mode"));
			SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
			SleedGameMode->PlayerEliminated(this, SleedPlayerController);
		}
	}
}

void ASleedCharacter::OnRep_Health()
{
	UpdateHUDHealth();
}

void ASleedCharacter::UpdateHUDHealth()
{
	SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
	if (SleedPlayerController)
	{
		SleedPlayerController->SetHUDHealth(Health, MaxHealth);
	}
}

bool ASleedCharacter::IsAlive()
{
	return (Health > 0.f);
}

void ASleedCharacter::OnRep_Stamina()
{	
	UpdateHUDStamina();
}

void ASleedCharacter::UpdateHUDStamina()
{
	SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
	if (SleedPlayerController)
	{
		SleedPlayerController->SetHUDStamina(Stamina, MaxStamina);
	}
}

void ASleedCharacter::SetOverlappingWeapon(ABaseWeapon* Weapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(false);
	}
	OverlappingWeapon = Weapon;
	if (IsLocallyControlled())
	{
		if (OverlappingWeapon)
		{
			OverlappingWeapon->ShowPickupWidget(true);
		}
	}
}

void ASleedCharacter::OnRep_OverlappingWeapon(ABaseWeapon* LastWeapon)
{
	if (OverlappingWeapon)
	{
		OverlappingWeapon->ShowPickupWidget(true);
	}
	if (LastWeapon)
	{
		LastWeapon->ShowPickupWidget(false);
	}
}

bool ASleedCharacter::IsWeaponEquipped()
{
	return (Combat && Combat->EquippedWeapon);
}

void ASleedCharacter::Move(const FInputActionValue& Value)
{
	if (IsStunned()) return;
	
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (!bIsSliding)
	{
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
	else
	{	
		if (MovementVector.Y > 0.f)
		{
			ForwardSlide = FMath::Clamp(ForwardSlide + 0.05f, MinSlidePower, MaxSlidePower);
		}
		else if (MovementVector.Y < 0.f)
		{
			ForwardSlide = FMath::Clamp(ForwardSlide - 0.05f, MinSlidePower, MaxSlidePower);
		}

		if (MovementVector.X > 0.f)
		{
			RightSlide = FMath::Clamp(RightSlide + 0.05f, MinSlidePower, MaxSlidePower);
		}
		else if (MovementVector.X < 0.f)
		{
			RightSlide = FMath::Clamp(RightSlide - 0.05f, MinSlidePower, MaxSlidePower);
		}
	}
}

void ASleedCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();
	if (GetController())
	{ 
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void ASleedCharacter::Jump()
{	
	if (IsStunned()) return;

	// jump is called both on server and client - reasoning not found yet!
	if (JumpState == EJumpState::EJS_NoJump)
	{
		MovementComp->JumpZVelocity = firstJumpHeight;
		JumpState = EJumpState::EJS_FirstJump;

		NiagaraJumpEffect(FirstJumpEffect);
	}
	else if (JumpState == EJumpState::EJS_FirstJump)
	{
		if (Stamina < JumpCost) return;

		MovementComp->JumpZVelocity = secondJumpHeight;
		JumpState = EJumpState::EJS_SecondJump;

		Stamina = FMath::Clamp(Stamina - JumpCost, 0.f, MaxStamina);
		UpdateHUDStamina();

		NiagaraJumpEffect(SecondaryJumpEffect);
	}
	else if (JumpState == EJumpState::EJS_Swinging)
	{	
		ServerBreakCable();
		JumpState = EJumpState::EJS_FirstJump;
		MovementComp->JumpZVelocity = swingJumpHeight;
	}
	else if(this->JumpCurrentCount > 1)
	{
		return; // we can jump only two times pressing the button, but we want our JumpCurrentCount to not be limited to 2 only incase of 'special' launches etc
	}

	Super::Jump();
}

void ASleedCharacter::NiagaraJumpEffect(UNiagaraSystem* JumpEffect)
{	
	if (JumpEffect)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			this,
			JumpEffect,
			GetMesh()->GetSocketLocation(FName("JumpEffectSocket"))
		);
	}
}

void ASleedCharacter::Landed(const FHitResult& Hit)
{
	JumpState = EJumpState::EJS_NoJump;

	if (MovementComp && MovementComp->FallingLateralFriction != AirFriction)
	{
		MulticastChangeAirFriction(AirFriction);
	}
}

void ASleedCharacter::EquipButtonPressed()
{	
	if (IsStunned()) return;

	if (Combat)
	{
		if (HasAuthority())
		{
			Combat->EquipWeapon(OverlappingWeapon);
		}
		else
		{	
			// calling this on the client, executing it on the server
			ServerEquipButtonPressed();
		}
	}
}

void ASleedCharacter::ServerEquipButtonPressed_Implementation()
{
	if (Combat)
	{
		Combat->EquipWeapon(OverlappingWeapon);
	}
}

void ASleedCharacter::Sprint()
{	
	if (IsStunned()) return;

	if (Stamina <= 0) return;

	GetWorldTimerManager().ClearTimer(SprintTimer);

	if (HasAuthority())
	{
		MovementComp->MaxWalkSpeed = SprintSpeed;
		Stamina = FMath::Clamp(Stamina - SprintCost, 0.f, MaxStamina);
		UpdateHUDStamina();
	}
	else
	{	
		MovementComp->MaxWalkSpeed = SprintSpeed; // we set it locally
		ServerSprint(SprintSpeed, true); // we call the server to set it for everyone, we need to set it on both, else the version on client and version on server will have different values
	}

	GetWorldTimerManager().SetTimer(SprintTimer, this, &ASleedCharacter::SprintTimerFinished, MaxSprintTime);
}

void ASleedCharacter::SprintTimerFinished()
{	
	MovementComp->MaxWalkSpeed = OriginalSpeed; // we set it locally
	ServerSprint(OriginalSpeed, false); // we call the server to set it for everyone, we need to set it on both, else the version on client and version on server will have different values

}

void ASleedCharacter::ServerSprint_Implementation(float Speed, bool breduceStamina)
{
	MovementComp->MaxWalkSpeed = Speed;
	if (breduceStamina)
	{
		Stamina = FMath::Clamp(Stamina - SprintCost, 0.f, MaxStamina);
	}
}

void ASleedCharacter::AddGold(int32 AmountOfGold)
{
	SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
	if (SleedPlayerController)
	{
		SleedPlayerState = SleedPlayerState == nullptr ? Cast<ASleedPlayerState>(SleedPlayerController->PlayerState) : SleedPlayerState;
		if (SleedPlayerState)
		{
			SleedPlayerState->AddGold(AmountOfGold);
		}
	}
}

void ASleedCharacter::ChangeAirFrictionAndLunch(FVector LaunchPower)
{	
	if (MovementComp == nullptr) return;
	
	MulticastChangeAirFriction(GroundFriction);
	MovementComp->Launch(LaunchPower);
}

void ASleedCharacter::MulticastChangeAirFriction_Implementation(float Friction)
{
	MovementComp->FallingLateralFriction = Friction;
}

void ASleedCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);
	
	if (PrevMovementMode == MOVE_Falling && MovementComp->MovementMode != MOVE_Falling)
	{
		// keep for the future
	}
}

bool ASleedCharacter::IsStunned()
{
	return CharacterStunState > ECharacterStunState::ECS_Init;
}

void ASleedCharacter::XButtonPressed()
{	
	if (CharacterStunState != ECharacterStunState::ECS_Xstun) return;

	if (HasAuthority())
	{
		ButtonPresses++;
		UpdateStunButtonHUD(ButtonPresses);
		HandleButtonPress();
	}
	else
	{	
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("client"));
		ButtonPresses++; // we set it locally
		UpdateStunButtonHUD(ButtonPresses);
		ServerButtonPressed();
	}
}

void ASleedCharacter::ServerButtonPressed_Implementation()
{	
	ButtonPresses++;
	HandleButtonPress();
}

void ASleedCharacter::OnRep_CharStunState()
{	
	ButtonPresses = 0;
	StunWidgetVisibility(CharacterStunState);
}

void ASleedCharacter::ClientStunStateChanged_Implementation(ECharacterStunState StunState)
{	
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("manual client RPC"));
	CharacterStunState = StunState;
	ButtonPresses = 0;
	StunWidgetVisibility(CharacterStunState);
}

void ASleedCharacter::HandleButtonPress()
{	
	if (ButtonPresses >= 3)
	{	
		ServerChangeStunState(ECharacterStunState::ECS_Init);
	}
}

void ASleedCharacter::UpdateStunButtonHUD(int32 num)
{
	SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
	if (SleedPlayerController)
	{
		SleedPlayerController->SetHUDStunButtons(num);
	}
}

void ASleedCharacter::ChangeStunState(ECharacterStunState StunState)
{
	ServerChangeStunState(StunState);
}

void ASleedCharacter::ServerChangeStunState_Implementation(ECharacterStunState StunState)
{	
	if (CharacterStunState != StunState)
	{
		CharacterStunState = StunState;
		ButtonPresses = 0;
		StunWidgetVisibility(CharacterStunState);
	}
	else // if the previous and current value are the same, the CharacterStunState wont be replicated so we need to send the data to the client manually
	{
		CharacterStunState = StunState;
		ButtonPresses = 0;
		ClientStunStateChanged(StunState);
		StunWidgetVisibility(CharacterStunState);
	}
}

void ASleedCharacter::StunWidgetVisibility(ECharacterStunState StunState)
{	
	if(Controller)
	{
		SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
	}

	if (SleedPlayerController == nullptr) return;
	
	if (CharacterStunState == ECharacterStunState::ECS_Init)
	{
		SleedPlayerController->HandleStunWidget(false); // destroy stun widget
	}
	else if (CharacterStunState == ECharacterStunState::ECS_Xstun)
	{
		SleedPlayerController->HandleStunWidget(true); // add widget to screen
	}
	else if (CharacterStunState == ECharacterStunState::ECS_Zstun)
	{
		SleedPlayerController->HandleStunWidget(true); // add widget to screen
	}
}

void ASleedCharacter::RopeButtonPressed()
{	
	if (IsStunned()) return;

	if (JumpState != EJumpState::EJS_Swinging)
	{	
		ServerCreateCable();
	}
}

void ASleedCharacter::ServerCreateCable_Implementation()
{	
	if (OverlappingRopeSwing == nullptr) return;
	MulticastUpdateCable(false);
}

void ASleedCharacter::ServerBreakCable_Implementation()
{
	MulticastUpdateCable(true);
}

void ASleedCharacter::MulticastUpdateCable_Implementation(bool bBreak)
{	
	if (bBreak)
	{
		BreakSwing();
	}
	else
	{
		if (Cable)
		{
			if (!Cable->IsActive())
			{
				Cable->SetActive(true);
				Cable->SetVisibility(true);
			}

			FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
			Cable->AttachToComponent(GetMesh(), AttachmentRules, FName("RightHandSocket"));

			if (OverlappingRopeSwing)
			{
				Cable->SetAttachEndToComponent(OverlappingRopeSwing->GetRootComponent(), NAME_None);

				FVector CharacterLocation = GetActorLocation();
				RopeSwingLocation = OverlappingRopeSwing->GetActorLocation();

				float Distance = FVector::Dist(CharacterLocation, RopeSwingLocation);

				OverlappingRopeSwing->ShowPickupWidget(false);
			}

			JumpState = EJumpState::EJS_Swinging;
		}
	}
}

void ASleedCharacter::SetOverlappingRopeSwing(ARopeSwing* RopeSwing)
{
	if (OverlappingRopeSwing)
	{
		OverlappingRopeSwing->ShowPickupWidget(false);
	}
	OverlappingRopeSwing = RopeSwing;
	if (IsLocallyControlled())
	{
		if (OverlappingRopeSwing)
		{
			OverlappingRopeSwing->ShowPickupWidget(true);
		}
	}
}

void ASleedCharacter::OnRep_OverlappingRopeSwing(ARopeSwing* LastRopeSwing)
{
	if (OverlappingRopeSwing)
	{
		OverlappingRopeSwing->ShowPickupWidget(true);
	}
	if (LastRopeSwing)
	{
		LastRopeSwing->ShowPickupWidget(false);
	}
}

void ASleedCharacter::BreakSwing()
{
	if (Cable)
	{
		if (Cable->IsActive())
		{
			Cable->SetAttachEndToComponent(GetMesh(), NAME_None);
			Cable->SetVisibility(false);
			Cable->SetActive(false);
		}

		RopeSwingLocation = FVector::ZeroVector;
	}
}

void ASleedCharacter::RopeSwing(float DeltaTime)
{
	if (RopeSwingLocation.IsNearlyZero()) return;

	// character velocity
	FVector Velocity = MovementComp->Velocity;

	// distance between character and ropeswing point
	FVector MyLocation = GetActorLocation();
	FVector Distance = MyLocation - RopeSwingLocation;

	// get the direction of the distance vector
	FVector DistanceNormalized = Distance.GetSafeNormal();

	// how much of the character's velocity is aligned with the direction of the rope swing
	float DotProduct = FVector::DotProduct(Velocity, Distance);

	/*	FINAL FORCE: DotProduct * (-2.f) part means:
		When the dot product is positive, it means the character is moving in the same general direction as the rope swing.
		In this case, multiplying the dot product by - 2 will result in a negative force, which essentially means the force will act in the opposite direction
		of the character's velocity. This can create a decelerating effect, slowing down the character's movement and potentially facilitating a swinging motion.

		When the dot product is negative, it means the character is moving in the opposite direction of the rope swing.In this case,
		multiplying the dot product by - 2 will result in a positive force, which means the force will act in the same direction as the character's velocity.
		This can provide a slight additional push in the same direction as the character's movement, potentially aiding the swinging motion.
	*/

	FVector Force = DistanceNormalized * DotProduct * (-2.f);

	// Apply the force to the character's rigid body
	GetCharacterMovement()->AddForce(Force);

	AddSwingRotation(Distance, DeltaTime);
}

void ASleedCharacter::AddSwingRotation(FVector& Distance, float DeltaTime)
{
	// Exclude the Z-axis rotation
	Distance.Z = 15.0f;

	// Calculate the rotation using the modified direction vector
	FRotator DesiredRotation = (-Distance).Rotation();

	// Get the character's velocity
	FVector Velocity = GetVelocity();

	// Calculate the dot product between the distance vector and velocity vector
	float DotProduct = FVector::DotProduct(Distance.GetSafeNormal(), Velocity.GetSafeNormal());

	// Adjust the desired rotation based on the dot product and velocity
	float MinDotProduct = 0.0f; // Minimum dot product value to rotate
	DesiredRotation.Yaw = FMath::Lerp(DesiredRotation.Yaw, GetActorRotation().Yaw, FMath::Clamp(DotProduct, MinDotProduct, 1.0f));

	// Interpolate between the current rotation and the desired rotation
	float InterpSpeed = 3.0f; // Adjust this value to control the rotation speed
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), DesiredRotation, DeltaTime, InterpSpeed);

	// Set the rotation for your character
	SetActorRotation(NewRotation);
}

void ASleedCharacter::Slide()
{	
	if (Controller)
	{	
		/*
		FRotator Rotation = Controller->GetControlRotation();
		FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, ForwardSlide);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDirection, RightSlide);
		*/
		
		FVector ForwardVector = GetActorForwardVector();
		// Convert the forward vector to a rotation
		FRotator ForwardRotation = FRotationMatrix::MakeFromX(ForwardVector).Rotator();
		// Calculate the right vector based on the forward rotation
		FVector RightVector = ForwardRotation.RotateVector(FVector::RightVector);
		// Add movement input using the forward and right vectors
		AddMovementInput(ForwardVector, ForwardSlide);
		AddMovementInput(RightVector, RightSlide);
		
	}
}

void ASleedCharacter::setIsSliding(bool bSlides)
{
	bIsSliding = bSlides;
	
	if(bIsSliding)
	{	
		if (MovementComp)
		{	
			bUseControllerRotationYaw = true;
			MovementComp->bOrientRotationToMovement = false;
			MovementComp->RotationRate = FRotator(0.f, 100.f, 0.f);
		}
	}
	else
	{	
		if (MovementComp)
		{	
			bUseControllerRotationYaw = false;
			MovementComp->bOrientRotationToMovement = true;
			MovementComp->RotationRate = FRotator(0.f, 400.f, 0.f);
		}
	}
	
	ForwardSlide = InitialSlidePower;
	RightSlide = InitialSlidePower / 2;
}

void ASleedCharacter::OnRep_IsSliding()
{	
	if (bIsSliding)
	{
		if (MovementComp)
		{	
			bUseControllerRotationYaw = true;
			MovementComp->bOrientRotationToMovement = false;
			MovementComp->RotationRate = FRotator(0.f, 100.f, 0.f);
		}
	}
	else
	{
		if (MovementComp)
		{	
			bUseControllerRotationYaw = false;
			MovementComp->bOrientRotationToMovement = true;
			MovementComp->RotationRate = FRotator(0.f, 400.f, 0.f);
		}
	}

	ForwardSlide = InitialSlidePower;
	RightSlide = InitialSlidePower / 2;
}

void ASleedCharacter::Celebrate()
{
	/*
	if (bIsCelebrating)
	{
		bIsCelebrating = false;
	}
	else
	{
		bIsCelebrating = true;
	}
	*/

	ElimTimerFinished();
}

void ASleedCharacter::GameMenu()
{	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("pressed P"));
	SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
	if (SleedPlayerController)
	{
		SleedPlayerController->SetGameMenuWidget();
	}
}

//
// Death
//
void ASleedCharacter::Elim()
{
	MulticastElim();
	GetWorldTimerManager().SetTimer(
		ElimTimer,
		this,
		&ASleedCharacter::ElimTimerFinished,
		ElimDelay
	);
}

void ASleedCharacter::MulticastElim_Implementation()
{
	bElimmed = true;
	PlayElimMontage();

	// Disable character movement
	GetCharacterMovement()->DisableMovement();
	GetCharacterMovement()->StopMovementImmediately();
	if (SleedPlayerController)
	{
		DisableInput(SleedPlayerController);
	}
	// Disable collision
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASleedCharacter::PlayElimMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ElimMontage)
	{
		AnimInstance->Montage_Play(ElimMontage);
	}
}

void ASleedCharacter::ElimTimerFinished()
{
	ASleedGameMode* SleedGameMode = GetWorld()->GetAuthGameMode<ASleedGameMode>();
	if (SleedGameMode)
	{
		SleedGameMode->RequestRespawn(this, Controller);
	}
}

// Aim Functions

void ASleedCharacter::AimTrigger()
{
	PlayThrowMontage();
}

void ASleedCharacter::PlayThrowMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && ThrowMontage)
	{
		AnimInstance->Montage_Play(ThrowMontage);
	}
}

void ASleedCharacter::Throw()
{
	const FRotator Rotation = Controller->GetControlRotation();

	// Calculate the arrow direction based on the camera rotation
	FVector ArrowDirection = Rotation.Vector() + FVector(0, 0, ThrowPitchOffset);
	ArrowDirection.Normalize();

	// Calculate the arrow end point
	FVector ArrowStart = GetMesh()->GetSocketLocation(FName("ThrowSocket"));
	FVector ArrowEnd = ArrowStart + (ArrowDirection * 1000.f); // You can adjust the length of the arrow as needed

	FColor ArrowColor = FColor::Red;
	float ArrowLifeTime = 5.0f; // Arrow will stay visible for 5 seconds

	// Draw the debug arrow
	UKismetSystemLibrary::DrawDebugArrow(GetWorld(), ArrowStart, ArrowEnd, 10.f, ArrowColor, 5.f, ArrowLifeTime);
}
