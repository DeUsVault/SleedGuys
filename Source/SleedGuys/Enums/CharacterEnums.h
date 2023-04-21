#pragma once

UENUM(BlueprintType)
enum class EWeaponState : uint8
{
	EWS_Initial UMETA(DisplayName = "Initial State"),
	EWS_Equipped UMETA(DisplayName = "Equipped"),
	EWS_Dropped UMETA(DisplayName = "Dropped"),

	EWS_MAX UMETA(DisplayName = "DefaultMAX")
};

UENUM(BlueprintType)
enum class EDeathPose : uint8
{
	EDP_Alive UMETA(DisplayName = "Alive"),
	EDP_Dead UMETA(DisplayName = "Dead")
};

UENUM(BlueprintType)
enum class ECharacterStunState : uint8
{
	ECS_Init UMETA(DisplayName = "Initial"),
	ECS_Xstun UMETA(DisplayName = "X stunned"),
	ECS_Zstun UMETA(DisplayName = "Z stunned")
};

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
	EES_Patrolling UMETA(DisplayName = "Patrolling"),
	EES_Chasing UMETA(DisplayName = "Chasing"),
	EES_Attacking UMETA(DisplayName = "Attacking"),
	EES_Spellcasting UMETA(DisplayName = "Spellcasting")
};