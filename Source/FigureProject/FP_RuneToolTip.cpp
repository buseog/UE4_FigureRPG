// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_RuneToolTip.h"

bool UFP_RuneToolTip::Initialize()
{
	Super::Initialize();

	return true;
}

void UFP_RuneToolTip::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

}

void UFP_RuneToolTip::ToggleToolTip(UButton* _slot)
{
	AddToViewport();
}