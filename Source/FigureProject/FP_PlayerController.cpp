// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_PlayerController.h"
#include "FP_StatusWidget.h"
#include "FP_Player.h"
#include "FP_StageWidget.h"
#include "FP_GameStart.h"
#include "FP_MainUI.h"


AFP_PlayerController::AFP_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bShowMainUI = false;

	

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

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_MainUI.FP_MainUI_C'");
	UClass* MainUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UUserWidget* MainUIWidget = CreateWidget<UFP_MainUI>(this, MainUI);
	WidgetMap.Add(MAINUI, MainUIWidget);

	WidgetMap[GAMESTART]->AddToViewport();
	WidgetMap[STAGE]->AddToViewport();
	
	
	WidgetMap[GAMESTART]->SetVisibility(ESlateVisibility::Visible);
	WidgetMap[STAGE]->SetVisibility(ESlateVisibility::Hidden);
	

	WidgetMap[STATUS]->SetRenderTranslation(FVector2D(200.f, 500.f));




}

void AFP_PlayerController::ToggleMainUI()
{
	if (nullptr == WidgetMap[MAINUI])
		return;

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);


	if (bShowMainUI)
	{
		bShowMainUI = false;
		Cast<UFP_MainUI>(WidgetMap[MAINUI])->eState = UFP_MainUI::END;

		PC->SetPause(false);
		
	}
	else
	{
		if (WidgetMap[MAINUI]->IsInViewport() == true)
			return;

		bShowMainUI = true;
		Cast<UFP_MainUI>(WidgetMap[MAINUI])->TimeAcc = 0.f;
		Cast<UFP_MainUI>(WidgetMap[MAINUI])->eState = UFP_MainUI::START;
		WidgetMap[MAINUI]->AddToViewport();

		PC->SetPause(true);
	}
}

void AFP_PlayerController::SetVisibility(eWIDGET _WidgetNum, bool _isvisible)
{
	if(_isvisible == true)
		WidgetMap[_WidgetNum]->SetVisibility(ESlateVisibility::Visible);
	else
		WidgetMap[_WidgetNum]->SetVisibility(ESlateVisibility::Hidden);
}