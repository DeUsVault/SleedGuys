#pragma once

UENUM(BlueprintType)
enum class EDamageTypes : uint8
{	
	EDT_Simple UMETA(DisplayName = "Simple"),
	EDT_Blood UMETA(DisplayName = "Blood"),
	EDT_Fire UMETA(DisplayName = "FireType"),
	EDT_Lighting UMETA(DisplayName = "LightingType"),

	EDT_Default UMETA(DisplayName = "Default")
};