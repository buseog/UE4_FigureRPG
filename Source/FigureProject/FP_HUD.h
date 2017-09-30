// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FP_Item.h"
#include "FP_HUD.generated.h"

/**
 * 
 */
class AFP_Inventory;
UCLASS()
class FIGUREPROJECT_API AFP_HUD : public AHUD
{
	GENERATED_BODY()

public:
	AFP_HUD();

private:
	AFP_Inventory* Inventory;
	APlayerController* PController;
	float CanvasSizeX;
	AFP_Item* Item;
	UFont* HudFont;

public:
	virtual void DrawHUD() override;
	virtual void BeginPlay() override;
	void OpenInventory();
	void PickupItem();
	void DrawWidgets();
	void Clicked();
};
