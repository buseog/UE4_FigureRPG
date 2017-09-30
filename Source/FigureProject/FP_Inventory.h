// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_HUD.h"
#include "FP_Item.h"
#include "FP_Inventory.generated.h"

/**
 * 
 */
struct Icon
{
	FString Name;
	UTexture2D* Texture;

	Icon()
	{
		Name = "Unknown";
		Texture = 0;
	}

	Icon(FString& _Name, UTexture2D* _Texture)
	{
		Name = _Name;
		Texture = _Texture;
	}
};

struct Widget
{
	Icon ItemIcon;
	FVector2D Pos, Size;

	bool Clicked(FVector2D Point)
	{
		return Point.X > Left() && Point.X < Right() && Point.Y > Top() && Point.Y < Bottom();
	}

	Widget(Icon _Icon)
	{
		ItemIcon = _Icon;
	}

	float Left()
	{
		return Pos.X;
	}

	float Right()
	{
		return Pos.X + Size.X;
	}

	float Top()
	{
		return Pos.Y;
	}

	float Bottom()
	{
		return Pos.Y + Size.Y;
	}
};

UCLASS()
class FIGUREPROJECT_API AFP_Inventory : public AFP_HUD
{
	GENERATED_BODY()

private:
	APlayerController* PController;
	bool bInventoryShowing;	
	TMap<FString, int> BackPack;
	TMap<FString, UTexture2D*> Icons;
	TArray<Widget> Widgets;
	
public:
	AFP_Inventory();

public:
	virtual void BeginPlay() override;
	void ToggleInventory(float CanvasSizeX);
	void AddWidget(Widget _Widgets, float CanvasSizeX);
	void AddItem(AFP_Item* Item);
	TArray<Widget> GetWidgets();
};
