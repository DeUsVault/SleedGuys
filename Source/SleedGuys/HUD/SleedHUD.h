// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SleedHUD.generated.h"

class UUserWidget;
class UCharacterOverlay;
class UButtonPresser;
class UGameMenu;
class UEndLevelWidget;

/**
 * 
 */
UCLASS()
class SLEEDGUYS_API ASleedHUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Player Stats")
	TSubclassOf<UUserWidget> CharacterOverlayClass;

	UCharacterOverlay* CharacterOverlay;

	// custom widget for when character is stunned - press button 'X' times to unstun
	UPROPERTY(EditAnywhere, Category = "Custom Widgets")
	TSubclassOf<UButtonPresser> ButtonPresserClass;

	UButtonPresser* ButtonPresser;

	void HandleStunWidgetHUD(bool bCreate);

	// custom widget for when character is stunned - press button 'X' times to unstun
	UPROPERTY(EditAnywhere, Category = "Custom Widgets")
	TSubclassOf<UGameMenu> GameMenuWidgetClass;

	UGameMenu* GameMenu;

	UGameMenu* HandleGameWidget();

	// custom widget for level ending
	UPROPERTY(EditAnywhere, Category = "Custom Widgets")
	TSubclassOf<UEndLevelWidget> EndLevelWidgetClass;

	UEndLevelWidget* EndLevelWidget;

	void AddEndLevelWidget();
protected:
	virtual void BeginPlay() override;
	void AddCharacterOverlay();
	
};
