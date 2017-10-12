// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_PlayerController.h"
#include "FP_StatusWidget.h"
#include "FP_Player.h"
#include "FP_StageWidget.h"



AFP_PlayerController::AFP_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bShowStatus = false;

	FName Path = TEXT("WidgetBlueprint'/Game/FP_StatusWidget_BP.FP_StatusWidget_BP_C'");
	UClass* Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	StatusUI = Widget;
}

void AFP_PlayerController::BeginPlay()
{
	FName Path = TEXT("WidgetBlueprint'/Game/FP_Stage_BP.FP_Stage_BP_C'");
	UClass* Widget2 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_StageWidget* StageWidget = CreateWidget<UFP_StageWidget>(this, Widget2);

	StageWidget->AddToViewport();
	StageWidget->SetVisibility(ESlateVisibility::Visible);

	if (nullptr != StatusUI)
	{
		if (nullptr == StatusWidget)
		{
			StatusWidget = CreateWidget<UFP_StatusWidget>(this, StatusUI);
			
			if (nullptr == StatusWidget)
				return;

			StatusWidget->AddToViewport();
			StatusWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AFP_PlayerController::ToggleStatus()
{
	if (nullptr == StatusWidget)
		return;

	if (bShowStatus)
	{
		bShowStatus = false;
		StatusWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		bShowStatus = true;
		StatusWidget->SetVisibility(ESlateVisibility::Visible);
	}
}