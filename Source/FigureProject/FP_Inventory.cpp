// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Inventory.h"
#include "FP_PlayerController.h"

AFP_Inventory::AFP_Inventory()
{
	
}

void AFP_Inventory::BeginPlay()
{
	bInventoryShowing = false;
	PController = GetWorld()->GetFirstPlayerController();
}

void AFP_Inventory::ToggleInventory(float CanvasSizeX)
{
	if (bInventoryShowing)
	{
		Widgets.Empty();
		bInventoryShowing = false;
		//PController->bShowMouseCursor = false;
		return;
	}

	bInventoryShowing = true;
	//PController->bShowMouseCursor = true;

	for (TMap<FString, int>::TIterator it = BackPack.CreateIterator();it; ++it)
	{
		FString Text = it->Key + FString::Printf(TEXT(" X %d"), it->Value);
		UTexture2D* Texture = nullptr;

		if (Icons.Find(it->Key))
			Texture = Icons[it->Key];

		AddWidget(Widget(Icon(Text, Texture)), CanvasSizeX);
	}
}

void AFP_Inventory::AddWidget(Widget _Widget, float CanvasSizeX)
{
	FVector2D Start(200, 200), Pad(12, 12);
	_Widget.Size = FVector2D(100, 100);
	_Widget.Pos = Start;
	
	for (int i = 0; i < Widgets.Num(); ++i)
	{
		_Widget.Size.X += _Widget.Size.X + Pad.X;

		if(_Widget.Pos.X + _Widget.Size.X > CanvasSizeX)
		{
			_Widget.Pos.X = Start.X;
			_Widget.Pos.Y += _Widget.Size.Y + Pad.Y;
		}
	}

	Widgets.Add(_Widget);
}

void AFP_Inventory::AddItem(AFP_Item* Item)
{
	if (BackPack.Find(Item->Name))
		BackPack[Item->Name] += Item->Quantity;
	else 
	{
		BackPack.Add(Item->Name, Item->Quantity);
		Icons.Add(Item->Name, Item->Icon);
	}
}

TArray<Widget> AFP_Inventory::GetWidgets()
{
	return Widgets;
}