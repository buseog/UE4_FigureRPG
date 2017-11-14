// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Button.h"
#include "FP_Rune.h"
#include "FP_Player.h"
#include "FP_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class FIGUREPROJECT_API UFP_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	enum SORTORDER{COLOR, TIER, RED, GREEN, BLUE, TIER1, TIER2, TIER3};

public:
	TArray<UButton*> Slots;
	UButton* ByTier;
	UButton* ByColor;
	UButton* ViewTier1;
	UButton* ViewTier2;
	UButton* ViewTier3;
	UButton* ViewRed;
	UButton* ViewGreen;
	UButton* ViewBlue;
	bool isClicked = false;
	int MaxSlotNum = 10;
	FVector2D IconSize = FVector2D(63.f, 62.f);
	AFP_Player* Player;
	class UCircularThrobber* Throbber;
	SORTORDER Order = TIER;
	bool bFromMain = true;
	AFP_Skill* SelectedSkill;
	
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
public:
	UFUNCTION()
	void SlotSelected();

	UFUNCTION()
	void SortInventory();

	UFUNCTION()
	void SortByTierClicked();

	UFUNCTION()
	void SortByColorClicked();

	UFUNCTION()
	void ViewTier1Clicked();

	UFUNCTION()
	void ViewTier2Clicked();

	UFUNCTION()
	void ViewTier3Clicked();

	UFUNCTION()
	void ViewRedClicked();

	UFUNCTION()
	void ViewGreenClicked();

	UFUNCTION()
	void ViewBlueClicked();

	void AddRune();
};