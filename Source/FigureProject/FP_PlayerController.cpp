// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_PlayerController.h"
#include "FP_StatusWidget.h"
#include "FP_Player.h"
#include "FP_StageWidget.h"
#include "FP_GameStart.h"


AFP_PlayerController::AFP_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bShowStatus = false;

	

}

void AFP_PlayerController::BeginPlay()
{
	
	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_StatusWidget_BP.FP_StatusWidget_BP_C'");
	UClass* Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_StatusWidget* StatusWidget = CreateWidget<UFP_StatusWidget>(this, Widget);
	WidgetMap.Add(STATUS, StatusWidget);

	FName GameStartWidget_Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_GameStart_BP.FP_GameStart_BP_C'");
	UClass* GameStart = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *GameStartWidget_Path.ToString()));
	UFP_GameStart* GameStartWidget = CreateWidget<UFP_GameStart>(this, GameStart);
	WidgetMap.Add(GAMESTART, GameStartWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Stage_BP.FP_Stage_BP_C'");
	UClass* Widget2 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UUserWidget* StageWidget = CreateWidget<UFP_StageWidget>(this, Widget2);
	WidgetMap.Add(STAGE, StageWidget);

	WidgetMap[GAMESTART]->AddToViewport();
	WidgetMap[STAGE]->AddToViewport();
	WidgetMap[STATUS]->AddToViewport();

	
	WidgetMap[GAMESTART]->SetVisibility(ESlateVisibility::Visible);
	WidgetMap[STATUS]->SetVisibility(ESlateVisibility::Hidden);
	WidgetMap[STAGE]->SetVisibility(ESlateVisibility::Hidden);

	//WidgetMap[STAGE]->SetRenderTranslation(FVector2D(500.f, 50.f));
	WidgetMap[STATUS]->SetRenderTranslation(FVector2D(0.f, 500.f));




}

void AFP_PlayerController::ToggleStatus()
{
	if (nullptr == WidgetMap[STATUS])
		return;

	if (bShowStatus)
	{
		bShowStatus = false;
		WidgetMap[STATUS]->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		bShowStatus = true;
		WidgetMap[STATUS]->SetVisibility(ESlateVisibility::Visible);
	}
}

void AFP_PlayerController::SetVisibility(int32 _WidgetNum, ESlateVisibility _visibility)
{
	WidgetMap[_WidgetNum]->SetVisibility(_visibility);
}