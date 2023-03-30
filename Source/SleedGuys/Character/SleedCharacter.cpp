// Fill out your copyright notice in the Description page of Project Settings.


#include "SleedCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "SleedGuys/Weapon/BaseWeapon.h"
#include "SleedGuys/SleederComponents/CombatComp.h"
#include "SleedGuys/SleederComponents/BuffComponent.h"
#include "SleedGuys/PlayerController/SleedPlayerController.h"

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

		SleedPlayerController->SetHUDHealth(Health, MaxHealth);
		SleedPlayerController->SetHUDStamina(Stamina, MaxStamina);
	}

	Tags.Add(FName("SleedCharacter"));
}

void ASleedCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
	}
}

void ASleedCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASleedCharacter, OverlappingWeapon, COND_OwnerOnly);
	DOREPLIFETIME(ASleedCharacter, bShouldDoubleJump);
	DOREPLIFETIME(ASleedCharacter, Health);
	DOREPLIFETIME(ASleedCharacter, Stamina);
	DOREPLIFETIME(ASleedCharacter, Gold);
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

void ASleedCharacter::OnRep_Health()
{

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
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);

	/*const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetActorRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = GetActorForwardVector();
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FVector::CrossProduct(ForwardDirection, FVector(0.f, 0.f, 1.f));
	AddMovementInput(RightDirection, MovementVector.X);*/
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
{	// jump is called both on server and client - reasoning not found yet!
	if (this->JumpCurrentCount == 0)
	{
		GetCharacterMovement()->JumpZVelocity = firstJumpHeight;
		bShouldDoubleJump = false;
	}
	else if (this->JumpCurrentCount == 1)
	{
		if (Stamina <= 0) return;

		GetCharacterMovement()->JumpZVelocity = secondJumpHeight;
		bShouldDoubleJump = true;

		Stamina = FMath::Clamp(Stamina - JumpCost, 0.f, MaxStamina);
		UpdateHUDStamina();
	}

	Super::Jump();
}

void ASleedCharacter::Landed(const FHitResult& Hit)
{
	bShouldDoubleJump = false;
}

void ASleedCharacter::EquipButtonPressed()
{
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
	if (Stamina <= 0) return;

	GetWorldTimerManager().ClearTimer(SprintTimer);

	if (HasAuthority())
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		Stamina = FMath::Clamp(Stamina - SprintCost, 0.f, MaxStamina);
		UpdateHUDStamina();
	}
	else
	{	
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; // we set it locally
		ServerSprint(SprintSpeed, true); // we call the server to set it for everyone, we need to set it on both, else the version on client and version on server will have different values
	}

	GetWorldTimerManager().SetTimer(SprintTimer, this, &ASleedCharacter::SprintTimerFinished, MaxSprintTime);
}

void ASleedCharacter::SprintTimerFinished()
{	
	GetCharacterMovement()->MaxWalkSpeed = OriginalSpeed; // we set it locally
	ServerSprint(OriginalSpeed, false); // we call the server to set it for everyone, we need to set it on both, else the version on client and version on server will have different values

}

void ASleedCharacter::ServerSprint_Implementation(float Speed, bool breduceStamina)
{	
	GetCharacterMovement()->MaxWalkSpeed = Speed;
	if (breduceStamina)
	{
		Stamina = FMath::Clamp(Stamina - SprintCost, 0.f, MaxStamina);
	}
}

void ASleedCharacter::AddGold(int32 AmountOfGold)
{
	Gold += AmountOfGold;
	UpdateHUDGold(); // coin pickup happens only on the server
	if (HasAuthority())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("authority"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::FromInt(AmountOfGold));
		}
	}
	else 
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, TEXT("noobie"));
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::FromInt(AmountOfGold));
		}
	}
}

void ASleedCharacter::OnRep_Gold()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("replicatingggg"));
	}
	UpdateHUDGold();
}

void ASleedCharacter::UpdateHUDGold()
{
	SleedPlayerController = SleedPlayerController == nullptr ? Cast<ASleedPlayerController>(Controller) : SleedPlayerController;
	if (SleedPlayerController)
	{
		SleedPlayerController->SetHUDGold(Gold);
	}
}
