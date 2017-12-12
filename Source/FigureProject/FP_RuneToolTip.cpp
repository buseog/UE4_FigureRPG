// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_RuneToolTip.h"
#include "FP_PlayerController.h"
#include "FP_InventoryWidget.h"
#include "FP_Tooltip.h"
#include "FP_ComRuneGenerator.h"
#include "FP_ComMessageUI.h"


AFP_Rune* UFP_RuneToolTip::SelectedRune = nullptr;
bool UFP_RuneToolTip::Initialize()
{
	Super::Initialize();

	EquipButton = Cast<UButton>(GetWidgetFromName(TEXT("EquipBtn")));
	EquipButton->OnClicked.AddDynamic(this, &UFP_RuneToolTip::EquipRune);

	DeleteButton = Cast<UButton>(GetWidgetFromName(TEXT("Delete")));
	DeleteButton->OnClicked.AddDynamic(this, &UFP_RuneToolTip::DeleteRune);

	UButton* GambleButton = Cast<UButton>(GetWidgetFromName(TEXT("Gamble")));
	GambleButton->OnClicked.AddDynamic(this, &UFP_RuneToolTip::Gamble);


	UButton* Prop1Button = Cast<UButton>(GetWidgetFromName(TEXT("Prop1")));
	Prop1Button->OnClicked.AddDynamic(this, &UFP_RuneToolTip::ChangeOptionRune);
	PropButtonArray.Add(Prop1Button);
	UButton* Prop2Button = Cast<UButton>(GetWidgetFromName(TEXT("Prop2")));
	Prop2Button->OnClicked.AddDynamic(this, &UFP_RuneToolTip::ChangeOptionRune);
	PropButtonArray.Add(Prop2Button);
	UButton* Prop3Button = Cast<UButton>(GetWidgetFromName(TEXT("Prop3")));
	Prop3Button->OnClicked.AddDynamic(this, &UFP_RuneToolTip::ChangeOptionRune);
	PropButtonArray.Add(Prop3Button);


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
			if (_rune->Option[i].IsEmpty())
				break;

			Val1 = FText::FromString(_rune->Discription[i]);

			break;
		case 1:
			if (_rune->Option[i].IsEmpty())
				break;

			Val2 = FText::FromString(_rune->Discription[i]);

			break;
		case 2:
			if (_rune->Option[i].IsEmpty())
				break;

			Val3 = FText::FromString(_rune->Discription[i]);

			break;
		case 3:
			if (_rune->Option[i].IsEmpty())
				break;

			Val4 = FText::FromString(_rune->Discription[i]);

			break;
		}

		type.Empty();
	}

	//Name = FText::FromString(_rune->Name);
	Tier = FText::FromString(FString::FromInt(_rune->Stat.Tier) + " Tier");

	if (_fromInventory)
	{
		EquipButton->SetVisibility(ESlateVisibility::Hidden);
		DeleteButton->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		EquipButton->SetVisibility(ESlateVisibility::Visible);
		DeleteButton->SetVisibility(ESlateVisibility::Hidden);
	}
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

	//Cast<UFP_InventoryWidget>(InventoryWidget)->SortInventory();

	this->RemoveFromViewport();
	InventoryWidget->RemoveFromViewport();

	PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->AddToViewport();
	PC->GetWidgetMap(AFP_PlayerController::SKILLTOOLTIP)->AddToViewport();

	SkillToolTip->CurrentSkill->RuneChanged = true;
}
void UFP_RuneToolTip::DeleteRune()
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (nullptr == pPlayer)
		return;

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);


	int iFound = 0;
	if (false == pPlayer->Inventory.Find(SelectedRune, iFound))
		return;

	pPlayer->Inventory.RemoveAt(iFound);
	SelectedRune->Destroy();
	SelectedRune = nullptr;
	Cast<UFP_InventoryWidget>(PC->GetWidgetMap(AFP_PlayerController::INVENTORY))->SortInventory();

	RemoveFromViewport();
}

void UFP_RuneToolTip::Gamble()
{
	for (int i = 0; i < SelectedRune->Discription.Num(); ++i)
	{
		PropButtonArray[i]->SetIsEnabled(true);
	}
}

void UFP_RuneToolTip::ChangeOptionRune()
{
	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player->Gem <= 0)
	{
		APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
		AFP_ComMessageUI::ShowMessage(PC, FText::FromString(TEXT("No Gems")), 2.f, FColor::Red);
		return;
	}
		

	Player->Gem--;
	AFP_ComRuneGenerator* runeGenerator = AFP_ComRuneGenerator::StaticClass()->GetDefaultObject<AFP_ComRuneGenerator>();
	for (int i = 0; i < PropButtonArray.Num(); ++i)
	{
		if (PropButtonArray[i]->IsPressed())
		{
			int index = 0;
			int j = 0;

			switch (i)
			{
			case 0:
				for (; j < SelectedRune->Discription.Num(); ++j)
				{
					if (Val1.ToString() == SelectedRune->Discription[j])
						index = j;
				}
				break;

			case 1:
				for (; j < SelectedRune->Discription.Num(); ++j)
				{
					if (Val2.ToString() == SelectedRune->Discription[j])
						index = j;
				}
				break;

			case 2:
				for (; j < SelectedRune->Discription.Num(); ++j)
				{
					if (Val3.ToString() == SelectedRune->Discription[j])
						index = j;
				}
				break;
			}

			AFP_ComRuneGenerator::ChangeOption(index, runeGenerator->RuneProperty, runeGenerator->RedRuneOption, runeGenerator->GreenRuneOption, runeGenerator->BlueRuneOption, runeGenerator->RuneStat);
			break;
		}
	}

	for (int i = 0; i < PropButtonArray.Num(); ++i)
		PropButtonArray[i]->SetIsEnabled(false);



	////
	InitializeToolTip();

	TArray<AFP_Rune::TYPE> type;
	FString option;

	for (int i = 0; i < SelectedRune->Option.Num(); ++i)
		Option.Add(FText::FromString(SelectedRune->Option[i]));

	for (int i = 0; i < Option.Num(); ++i)
	{
		SelectedRune->Stat.Type.MultiFind(SelectedRune->Option[i], type, true);

		switch (i)
		{
		case 0:
			if (SelectedRune->Option[i].IsEmpty())
				break;

			Val1 = FText::FromString(SelectedRune->Discription[i]);

			break;
		case 1:
			if (SelectedRune->Option[i].IsEmpty())
				break;

			Val2 = FText::FromString(SelectedRune->Discription[i]);

			break;
		case 2:
			if (SelectedRune->Option[i].IsEmpty())
				break;

			Val3 = FText::FromString(SelectedRune->Discription[i]);

			break;
		case 3:
			if (SelectedRune->Option[i].IsEmpty())
				break;

			Val4 = FText::FromString(SelectedRune->Discription[i]);

			break;
		}

		type.Empty();
	}

	Tier = FText::FromString(FString::FromInt(SelectedRune->Stat.Tier) + " Tier");

}