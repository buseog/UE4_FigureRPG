// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_RuneToolTip.h"
#include "FP_PlayerController.h"
#include "FP_InventoryWidget.h"

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

			if (_rune->OptionVal[i] == NULL)
				break;
			
			Val1 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));
			break;
		case 1:
			Option2 = Option[i];

			if (_rune->OptionVal[i] == NULL)
				break;

			Val2 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));
			break;
		case 2:
			Option3 = Option[i];

			if (_rune->OptionVal[i] == NULL)
				break;

			Val3 = FText::FromString(FString::SanitizeFloat(_rune->OptionVal[i]));
			break;
		case 3:
			Option4 = Option[i];

			if (_rune->OptionVal[i] == NULL)
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
	TArray<AActor*> FoundActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_Weapon::StaticClass(), FoundActor);
	if (FoundActor[0] == nullptr)
		return;

	if(SelectedSkill->GetName().Contains("FireBall"))
		Cast<AFP_Weapon>(FoundActor[0])->EquipedRunes.Add(AFP_Weapon::SKILLTYPE::FIREBALL, SelectedRune);
	else if (SelectedSkill->GetName().Contains("FireWall"))
		Cast<AFP_Weapon>(FoundActor[0])->EquipedRunes.Add(AFP_Weapon::SKILLTYPE::FIREWALL, SelectedRune);
	else if (SelectedSkill->GetName().Contains("FireBlast"))
		Cast<AFP_Weapon>(FoundActor[0])->EquipedRunes.Add(AFP_Weapon::SKILLTYPE::FIREBLAST, SelectedRune);
	else if (SelectedSkill->GetName().Contains("IceBall"))
		Cast<AFP_Weapon>(FoundActor[0])->EquipedRunes.Add(AFP_Weapon::SKILLTYPE::ICEBALL, SelectedRune);
	else if (SelectedSkill->GetName().Contains("IceBlast"))
		Cast<AFP_Weapon>(FoundActor[0])->EquipedRunes.Add(AFP_Weapon::SKILLTYPE::ICEBLAST, SelectedRune);
	else if (SelectedSkill->GetName().Contains("IceOrb"))
		Cast<AFP_Weapon>(FoundActor[0])->EquipedRunes.Add(AFP_Weapon::SKILLTYPE::ICEORB, SelectedRune);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UUserWidget* InventoryWidget = PC->GetWidgetMap(AFP_PlayerController::INVENTORY);
	
	Player->Inventory.Remove(SelectedRune);
	Cast<UFP_InventoryWidget>(InventoryWidget)->SortInventory();

	this->RemoveFromViewport();
}