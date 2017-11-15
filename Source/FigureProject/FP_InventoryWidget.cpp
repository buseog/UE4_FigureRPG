// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_InventoryWidget.h"
#include "Engine.h"
#include "FP_PlayerController.h"
#include "FP_MainUI.h"
#include "FP_RuneToolTip.h"
#include "CircularThrobber.h"
#include "UniformGridSlot.h"
#include "FP_ComRuneGenerator.h"
#include "FP_MonsterMgr.h"


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
		Slots[i - 1]->SetIsEnabled(false);
	}

	ByTier = Cast<UButton>(GetWidgetFromName("SortByTier"));
	ByTier->OnClicked.AddDynamic(this, &UFP_InventoryWidget::SortByTierClicked);

	ByColor = Cast<UButton>(GetWidgetFromName("SortByColor"));
	ByColor->OnClicked.AddDynamic(this, &UFP_InventoryWidget::SortByColorClicked);

	ViewTier1 = Cast<UButton>(GetWidgetFromName("Tier1"));
	ViewTier1->OnClicked.AddDynamic(this, &UFP_InventoryWidget::ViewTier1Clicked);

	ViewTier2 = Cast<UButton>(GetWidgetFromName("Tier2"));
	ViewTier2->OnClicked.AddDynamic(this, &UFP_InventoryWidget::ViewTier2Clicked);

	ViewTier3 = Cast<UButton>(GetWidgetFromName("Tier3"));
	ViewTier3->OnClicked.AddDynamic(this, &UFP_InventoryWidget::ViewTier3Clicked);

	ViewRed = Cast<UButton>(GetWidgetFromName("Red"));
	ViewRed->OnClicked.AddDynamic(this, &UFP_InventoryWidget::ViewRedClicked);

	ViewGreen = Cast<UButton>(GetWidgetFromName("Green"));
	ViewGreen->OnClicked.AddDynamic(this, &UFP_InventoryWidget::ViewGreenClicked);

	ViewBlue = Cast<UButton>(GetWidgetFromName("Blue"));
	ViewBlue->OnClicked.AddDynamic(this, &UFP_InventoryWidget::ViewBlueClicked);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	if(PC != nullptr)
		PC->InputComponent->BindAction("AddItem", IE_Released, this, &UFP_InventoryWidget::AddRune);

	Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	Throbber = (UCircularThrobber*)GetWidgetFromName(TEXT("Active"));

	SelectedSkill = nullptr;

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

			UUniformGridSlot* ThrobberSlot = Cast<UUniformGridSlot>(Throbber->Slot);
			UUniformGridSlot* InventorySlot = Cast<UUniformGridSlot>(Slots[i]->Slot);
			ThrobberSlot->SetColumn(InventorySlot->Column);
			ThrobberSlot->SetRow(InventorySlot->Row);
			Throbber->SetVisibility(ESlateVisibility::Visible);
			Cast<UFP_RuneToolTip>(RuneToolTip)->ToggleToolTip(Player->Inventory[i], bFromMain, SelectedSkill);
		}
	}
}

void UFP_InventoryWidget::AddRune()
{
	if (Player->Inventory.Num() >= MaxSlotNum)
		return;

	AFP_Rune* rune = GetWorld()->SpawnActor<AFP_Rune>(FVector::ZeroVector, FRotator::ZeroRotator);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_MonsterMgr::StaticClass(), FoundActors);

	int stage = Cast<AFP_MonsterMgr>(FoundActors[0])->Stage;

	AFP_ComRuneGenerator* runeGenerator = AFP_ComRuneGenerator::StaticClass()->GetDefaultObject<AFP_ComRuneGenerator>();

	AFP_ComRuneGenerator::GenerateRune(runeGenerator->RuneProperty, runeGenerator->RedRuneOption, runeGenerator->GreenRuneOption, runeGenerator->BlueRuneOption, runeGenerator->RuneStat, rune, stage);

	Player->Inventory.Add(rune);

	//UE_LOG(LogClass, Log, TEXT("%f"), rune->Stat.Damage);
}

void UFP_InventoryWidget::SortInventory()
{
	for (int i = 0; i < Slots.Num(); ++i)
	{
		Slots[i]->WidgetStyle.Normal.SetResourceObject(NULL);
		Slots[i]->WidgetStyle.Hovered.SetResourceObject(NULL);
		Slots[i]->WidgetStyle.Pressed.SetResourceObject(NULL);
		Slots[i]->SetIsEnabled(false);
	}

	int slotNum = -1;

	if (Player->Inventory.Num() == 0)
		return;

	if (Order == TIER)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			return A.Stat.Tier < B.Stat.Tier;
		});
	}
	else if (Order == RED)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			return A.Color.R == 255.f;
		});
	}
	else if (Order == GREEN)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			return A.Color.G == 255.f;
		});
	}
	else if (Order == BLUE)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			return A.Color.B == 255.f;
		});
	}
	else if (Order == COLOR)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			if (A.Color.R == 0 && B.Color.R == 0)
				return A.Color.G > B.Color.G;

			return A.Color.R > B.Color.R;
		});
	}
	else if (Order == TIER1)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			return A.Stat.Tier == 1;
		});
	}
	else if (Order == TIER2)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			return A.Stat.Tier == 2;
		});
	}
	else if (Order == TIER2)
	{
		Player->Inventory.Sort([](AFP_Rune& A, AFP_Rune& B) {
			return A.Stat.Tier == 3;
		});
	}

	if (Order == COLOR || Order == TIER)
	{
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

			if (!Player->Inventory[i]->bEquiped)
				Slots[i]->SetIsEnabled(true);
			else
				Slots[i]->SetIsEnabled(false);
		}
	}
	else
	{
		for (int i = 0; i < Player->Inventory.Num(); ++i)
		{
			if (Order == RED && Player->Inventory[i]->Color != FColor::Red)
				continue;
			else if (Order == GREEN && Player->Inventory[i]->Color != FColor::Green)
				continue;
			else if (Order == BLUE && Player->Inventory[i]->Color != FColor::Blue)
				continue;
			else if (Order == TIER1 && Player->Inventory[i]->Stat.Tier != 1)
				continue;
			else if (Order == TIER2 && Player->Inventory[i]->Stat.Tier != 2)
				continue;
			else if (Order == TIER3 && Player->Inventory[i]->Stat.Tier != 3)
				continue;
			else
				++slotNum;

			Slots[slotNum]->WidgetStyle.Normal.SetResourceObject(Player->Inventory[i]->Icon);
			Slots[slotNum]->WidgetStyle.Normal.ImageSize = IconSize;
			Slots[slotNum]->WidgetStyle.Normal.Margin = 0;
			Slots[slotNum]->WidgetStyle.Hovered.SetResourceObject(Player->Inventory[i]->Icon);
			Slots[slotNum]->WidgetStyle.Hovered.ImageSize = IconSize;
			Slots[slotNum]->WidgetStyle.Hovered.Margin = 0;
			Slots[slotNum]->WidgetStyle.Pressed.SetResourceObject(Player->Inventory[i]->Icon);
			Slots[slotNum]->WidgetStyle.Pressed.ImageSize = IconSize;
			Slots[slotNum]->WidgetStyle.Pressed.Margin = 0;

			if (!Player->Inventory[i]->bEquiped)
				Slots[i]->SetIsEnabled(true);
			else
				Slots[i]->SetIsEnabled(false);
		}
	}
}

void UFP_InventoryWidget::SortByTierClicked()
{
	Order = TIER;
	SortInventory();
}

void UFP_InventoryWidget::SortByColorClicked()
{
	Order = COLOR;
	SortInventory();
}

void UFP_InventoryWidget::ViewTier1Clicked()
{
	Order = TIER1;
	SortInventory();
}

void UFP_InventoryWidget::ViewTier2Clicked()
{
	Order = TIER2;
	SortInventory();
}

void UFP_InventoryWidget::ViewTier3Clicked()
{
	Order = TIER3;
	SortInventory();
}

void UFP_InventoryWidget::ViewRedClicked()
{
	Order = RED;
	SortInventory();
}

void UFP_InventoryWidget::ViewGreenClicked()
{
	Order = GREEN;
	SortInventory();
}

void UFP_InventoryWidget::ViewBlueClicked()
{
	Order = BLUE;
	SortInventory();
}