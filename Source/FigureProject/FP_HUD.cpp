// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_HUD.h"
#include "FP_Inventory.h"
#include "Engine/Canvas.h"
#include "FP_PlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"


AFP_HUD::AFP_HUD()
{
	ConstructorHelpers::FObjectFinder<UFont> FontObject(TEXT("Font'/Game/Roboto-Regular_Font.Roboto-Regular_Font'"));
	HudFont = FontObject.Object;
}

void AFP_HUD::BeginPlay()
{
	Item = GetWorld()->SpawnActor<AFP_Item>();
	Inventory = GetWorld()->SpawnActor<AFP_Inventory>();
	PController = GetWorld()->GetFirstPlayerController();

	PController->InputComponent->BindAction("ToggleInventory", IE_Released, this, &AFP_HUD::OpenInventory);
	PController->InputComponent->BindAction("AddItem", IE_Released, this, &AFP_HUD::PickupItem);
	PController->InputComponent->BindAction("LeftClick", IE_Released, this, &AFP_HUD::Clicked);
}

void AFP_HUD::DrawHUD()
{
	Super::DrawHUD();

	CanvasSizeX = Canvas->SizeX;

	DrawWidgets();
}

void AFP_HUD::OpenInventory()
{
	Inventory->ToggleInventory(CanvasSizeX);
}

void AFP_HUD::PickupItem()
{
	Inventory->AddItem(Item);
}

void AFP_HUD::DrawWidgets()
{
	TArray<Widget> Widgets = Inventory->GetWidgets();
	
	for (int i = 0; i < Widgets.Num(); ++i)
	{
		DrawTexture((UTexture*)(Widgets[i].ItemIcon.Texture), Widgets[i].Pos.X, Widgets[i].Pos.Y, Widgets[i].Pos.X, Widgets[i].Pos.Y, 0, 0, 1, 1, FLinearColor::White, BLEND_Translucent, 0.5f);
		DrawText(Widgets[i].ItemIcon.Name, FLinearColor::Black, Widgets[i].Pos.X, Widgets[i].Pos.Y, HudFont, 2.f, false);
	}
}

void AFP_HUD::Clicked()
{
	TArray<Widget> Widgets = Inventory->GetWidgets();

	FVector2D MousePosition;

	PController->GetMousePosition(MousePosition.X, MousePosition.Y);

	for (int i = 0; i < Widgets.Num(); ++i)
	{
		if (Widgets[i].Clicked(MousePosition))
		{
			UE_LOG(LogClass, Log, TEXT("Clicked"));
		}
	}
}