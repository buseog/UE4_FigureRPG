// Fill out your copyright notice in the Description page of Project Settings.

#include "HPBar_Widget.h"



bool UHPBar_Widget::Initialize()
{
	Super::Initialize();

	ProgressBar = (UProgressBar*)GetWidgetFromName(TEXT("HPBar"));

	return true;
}

void UHPBar_Widget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	
}