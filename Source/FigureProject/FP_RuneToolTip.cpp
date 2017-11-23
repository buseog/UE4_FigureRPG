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

	TArray<AFP_Rune::TYPE> type;
	FString option;

	for (int i = 0; i < _rune->Option.Num(); ++i)
		Option.Add(FText::FromString(_rune->Option[i]));

	for (int i = 0; i < Option.Num(); ++i)
	{
		_rune->Stat.Type.MultiFind(_rune->Option[i], type, true);

		switch (i)
		{
		case 0:
			//Option1 = Option[i];

			/*if (_rune->OptionVal[i] == 0.f)
				break;*/

			/*for (int j = 0; j < type.Num(); ++j)
			{
				if(type[j] == AFP_Rune::STAT)
					option = "Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%";
				else if(type[j] == AFP_Rune::DEBUFF)
					option += FString::SanitizeFloat(_rune->OptionVal[i]);
			}
			Val1 = FText::FromString(option);
			option.Empty();*/

			Val1 = FText::FromString(_rune->Discription[i]);

			/*if(_rune->Stat.Type.FindRef(_rune->Option[i]) == AFP_Rune::STAT)
				Val1 = FText::FromString("Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%");
			else
				Val1 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));*/

			break;
		case 1:
			//Option2 = Option[i];

			/*if (_rune->OptionVal[i] == 0.f)
				break;*/

			/*for (int j = 0; j < type.Num(); ++j)
			{
				if (type[j] == AFP_Rune::STAT)
					option += "Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%";
				else
					option += FString::SanitizeFloat(_rune->OptionVal[i]);
			}
			Val2 = FText::FromString(option);
			option.Empty();*/

			Val2 = FText::FromString(_rune->Discription[i]);

			/*if (_rune->Stat.Type.FindRef(_rune->Option[i]) == AFP_Rune::STAT)
				Val2 = FText::FromString("Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%");
			else
				Val2 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));*/

			break;
		case 2:
			//Option3 = Option[i];

			/*if (_rune->OptionVal[i] == 0.f)
				break;*/

			/*for (int j = 0; j < type.Num(); ++j)
			{
				if (type[j] == AFP_Rune::STAT)
					option += "Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%";
				else
					option += FString::SanitizeFloat(_rune->OptionVal[i]);
			}
			Val3 = FText::FromString(option);
			option.Empty();*/

			Val3 = FText::FromString(_rune->Discription[i]);

			/*if (_rune->Stat.Type.FindRef(_rune->Option[i]) == AFP_Rune::STAT)
				Val3 = FText::FromString("Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%");
			else
				Val3 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));*/

			break;
		case 3:
			//Option4 = Option[i];

			/*if (_rune->OptionVal[i] == 0.f)
				break;*/

			/*for (int j = 0; j < type.Num(); ++j)
			{
				if (type[j] == AFP_Rune::STAT)
					option += "Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%";
				else
					option += FString::SanitizeFloat(_rune->OptionVal[i]);
			}
			Val4 = FText::FromString(option);
			option.Empty();*/

			Val4 = FText::FromString(_rune->Discription[i]);

			/*if (_rune->Stat.Type.FindRef(_rune->Option[i]) == AFP_Rune::STAT)
				Val4 = FText::FromString("Increase " + FString::FromInt(FMath::RoundHalfToEven(FMath::RoundHalfToEven((_rune->OptionVal[i] - 1) * 1000.f) / 10)) + "%");
			else
				Val4 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));*/

			break;
		}

		type.Empty();
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

	if(SkillToolTip->CurrentSkill->Sockets[SkillToolTip->iSocketIndex].Rune->IsValidLowLevel())
		SkillToolTip->CurrentSkill->Sockets[SkillToolTip->iSocketIndex].Rune->bEquiped = false;

	SkillToolTip->CurrentSkill->Sockets[SkillToolTip->iSocketIndex].EquipRune(SelectedRune, SkillToolTip->iSocketIndex, int(AFP_Weapon::ActiveSkill));
	Player->Inventory[Player->Inventory.Find(SelectedRune)]->bEquiped = true;

	Cast<UFP_InventoryWidget>(InventoryWidget)->SortInventory();

	this->RemoveFromViewport();
	InventoryWidget->RemoveFromViewport();

	PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->AddToViewport();
	PC->GetWidgetMap(AFP_PlayerController::SKILLTOOLTIP)->AddToViewport();

	SkillToolTip->CurrentSkill->RuneChanged = true;
}