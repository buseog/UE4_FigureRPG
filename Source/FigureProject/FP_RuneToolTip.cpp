// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_RuneToolTip.h"
#include "FP_PlayerController.h"

bool UFP_RuneToolTip::Initialize()
{
	Super::Initialize();

	return true;
}

void UFP_RuneToolTip::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

}

void UFP_RuneToolTip::ToggleToolTip(AFP_Rune* _rune)
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
			break;
		case 1:
			Option2 = Option[i];
			break;
		case 2:
			Option3 = Option[i];
			break;
		case 3:
			Option4 = Option[i];
			break;
		}
	}

	//Name = FText::FromString(_rune->Name);
	Tier = FText::FromString(FString::FromInt(_rune->Stat.Tier) + " Tier");

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