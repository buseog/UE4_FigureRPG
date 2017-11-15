// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_RuneToolTip.h"
#include "FP_PlayerController.h"
#include "FP_InventoryWidget.h"
#include "FP_Tooltip.h"

bool UFP_RuneToolTip::Initialize()
{
	Super::Initialize();

	EquipButton = Cast<UButton>(GetWidgetFromName(TEXT("EquipBtn")));

	EquipButton->OnClicked.AddDynamic(this, &UFP_RuneToolTip::EquipRune);

	return true;
}

void UFP_RuneToolTip::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

}

void UFP_RuneToolTip::ToggleToolTip(AFP_Rune* _rune, bool _fromInventory, AFP_Skill* _skill)
{
	if (IsInViewport())
		RemoveFromViewport();

	InitializeToolTip();

	for (int i = 0; i < _rune->Option.Num(); ++i)
		Option.Add(FText::FromString(_rune->Option[i]));

	for (int i = 0; i < Option.Num(); ++i)
	{
		switch (i)
		{
		case 0:
			Option1 = Option[i];

			if (_rune->OptionVal[i] == 0.f)
				break;
			
			Val1 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));
			break;
		case 1:
			Option2 = Option[i];

			if (_rune->OptionVal[i] == 0.f)
				break;

			Val2 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));
			break;
		case 2:
			Option3 = Option[i];

			if (_rune->OptionVal[i] == 0.f)
				break;

			Val3 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));
			break;
		case 3:
			Option4 = Option[i];

			if (_rune->OptionVal[i] == 0.f)
				break;

			Val4 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));
			break;
		}
	}

	//Name = FText::FromString(_rune->Name);
	Tier = FText::FromString(FString::FromInt(_rune->Stat.Tier) + " Tier");

	if (_fromInventory)
		EquipButton->SetVisibility(ESlateVisibility::Hidden);
	else
		EquipButton->SetVisibility(ESlateVisibility::Visible);

	SelectedSkill = _skill;
	SelectedRune = _rune;

	AddToViewport();
}

void UFP_RuneToolTip::InitializeToolTip()
{
	Option.Empty();
	Option1 = FText::FromString("");
	Option2 = FText::FromString("");
	Option3 = FText::FromString("");
	Option4 = FText::FromString("");
	Val1 = FText::FromString("");
	Val2 = FText::FromString("");
	Val3 = FText::FromString("");
	Val4 = FText::FromString("");
	Tier = FText::FromString("");
	//Name = FText::FromString("");
}

void UFP_RuneToolTip::EquipRune()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UUserWidget* InventoryWidget = PC->GetWidgetMap(AFP_PlayerController::INVENTORY);
	UFP_Tooltip* SkillToolTip = Cast<UFP_Tooltip>(PC->GetWidgetMap(AFP_PlayerController::SKILLTOOLTIP));

	SkillToolTip->CurrentSkill->Sockets[SkillToolTip->iSocketIndex].EquipRune(SelectedRune);
	
	Player->Inventory[Player->Inventory.Find(SelectedRune)]->bEquiped = true;
	Cast<UFP_InventoryWidget>(InventoryWidget)->SortInventory();

	this->RemoveFromViewport();
	InventoryWidget->RemoveFromViewport();

	PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->AddToViewport();
	PC->GetWidgetMap(AFP_PlayerController::SKILLTOOLTIP)->AddToViewport();
}