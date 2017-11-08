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
	TArray<UButton*> Slots;
	bool isClicked = false;
	int MaxSlotNum = 10;
	FVector2D IconSize = FVector2D(63.f, 62.f);
	AFP_Player* Player;
	class UCircularThrobber* Throbber;
	
public:
	virtual bool Initialize() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;
	
public:
	UFUNCTION()
	void SlotSelected();
	void AddRune();
	void ViewAllSortByTier();
};