// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_InventoryWidget.h"
#include "Engine.h"
#include "FP_PlayerController.h"
#include "FP_MainUI.h"
#include "FP_RuneToolTip.h"


bool UFP_InventoryWidget::Initialize()
{
	Super::Initialize();

	FString slotName;
	UButton* slot;

	for (int i = 1; i <= 10; ++i)
	{
		slotName = "Slot" + FString::FromInt(i);
		slot = Cast<UButton>(GetWidgetFromName(*slotName));
		slot->OnClicked.AddDynamic(this, &UFP_InventoryWidget::SlotSelected);
		Slots.Add(slot);
	}

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	if(PC != nullptr)
		PC->InputComponent->BindAction("AddItem", IE_Released, this, &UFP_InventoryWidget::AddRune);

	Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	return true;
}

void UFP_InventoryWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (!isClicked)
		isClicked = true;

	
}

void UFP_InventoryWidget::SlotSelected()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	for (int i = 0; i < Slots.Num(); ++i)
	{
		if (Slots[i]->IsPressed())
		{
			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			UUserWidget* RuneToolTip = Cast<AFP_PlayerController>(Controller)->GetWidgetMap(AFP_PlayerController::RUNETOOLTIP);

			Cast<UFP_RuneToolTip>(RuneToolTip)->ToggleToolTip(Slots[i]);
		}
	}
}

void UFP_InventoryWidget::AddRune()
{
	if (Player->Inventory.Num() >= MaxSlotNum)
		return;

	AFP_Rune* rune = GetWorld()->SpawnActor<AFP_Rune>(FVector::ZeroVector, FRotator::ZeroRotator);

	Player->Inventory.Add(rune);

	ViewAllSortByTier();
}

void UFP_InventoryWidget::ViewAllSortByTier()
{
	if (Player->Inventory.Num() == 0)
		return;

	/*Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
		if (A.Color.R == 0 && B.Color.R == 0)
			return A.Color.G > B.Color.G;

		return A.Color.R > B.Color.R;
	});*/

	Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
		return A.Stat.Tier < B.Stat.Tier;
	});

	for (int i = 0; i < Player->Inventory.Num(); ++i)
	{
		Slots[i]->WidgetStyle.Normal.SetResourceObject(Player->Inventory[i]->Icon);
		Slots[i]->WidgetStyle.Normal.ImageSize = IconSize;
		Slots[i]->WidgetStyle.Normal.Margin = 0;
		Slots[i]->WidgetStyle.Hovered.SetResourceObject(Player->Inventory[i]->Icon);
		Slots[i]->WidgetStyle.Hovered.ImageSize = IconSize;
		Slots[i]->WidgetStyle.Hovered.Margin = 0;
		Slots[i]->WidgetStyle.Pressed.SetResourceObject(Player->Inventory[i]->Icon);
		Slots[i]->WidgetStyle.Pressed.ImageSize = IconSize;
		Slots[i]->WidgetStyle.Pressed.Margin = 0;
	}
}