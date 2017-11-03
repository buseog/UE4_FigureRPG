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

	return true;
}

void UFP_InventoryWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	if (PC->bShowMainUI == false)
	{
		RemoveFromViewport();
		Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->isRuneClicked = false;
	}
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