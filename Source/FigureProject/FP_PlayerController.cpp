// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_PlayerController.h"
#include "FP_StatusWidget.h"
#include "FP_Player.h"
#include "FP_StageWidget.h"
#include "FP_GameStart.h"
#include "FP_MainUI.h"
#include "FP_SkillUI.h"
#include "FP_Tooltip.h"
#include "FP_InventoryWidget.h"
#include "FP_RuneToolTip.h"


AFP_PlayerController::AFP_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bShowMainUI = false; 	
}

void AFP_PlayerController::BeginPlay()
{

	
	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_StatusWidget_BP.FP_StatusWidget_BP_C'");
	TSubclassOf<UFP_StatusWidget> Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_StatusWidget* StatusWidget = CreateWidget<UFP_StatusWidget>(this, Widget);
	WidgetMap.Add(STATUS, StatusWidget);

	FName GameStartWidget_Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_GameStart_BP.FP_GameStart_BP_C'");
	TSubclassOf<UFP_GameStart> GameStart = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *GameStartWidget_Path.ToString()));
	UFP_GameStart* GameStartWidget = CreateWidget<UFP_GameStart>(this, GameStart);
	WidgetMap.Add(GAMESTART, GameStartWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Stage_BP.FP_Stage_BP_C'");
	TSubclassOf<UFP_StageWidget> Widget2 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_StageWidget* StageWidget = CreateWidget<UFP_StageWidget>(this, Widget2);
	WidgetMap.Add(STAGE, StageWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_MainUI.FP_MainUI_C'");
	TSubclassOf<UFP_MainUI> MainUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_MainUI* MainUIWidget = CreateWidget<UFP_MainUI>(this, MainUI);
	WidgetMap.Add(MAINUI, MainUIWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_SkillUI.FP_SkillUI_C'");
	TSubclassOf<UFP_SkillUI> SkillUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_SkillUI* SkillUIWidget = CreateWidget<UFP_SkillUI>(this, SkillUI);
	WidgetMap.Add(SKILLUI, SkillUIWidget);


	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	TSubclassOf<UFP_Tooltip> SkillToolTip = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_Tooltip* SkillToolTipWidget = CreateWidget<UFP_Tooltip>(this, SkillToolTip);
	SkillToolTipWidget->SetSKillUI(SkillUIWidget);
	WidgetMap.Add(SKILLTOOLTIP, SkillToolTipWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Inventory_BP.FP_Inventory_BP_C'");
	TSubclassOf<UFP_InventoryWidget> Inventory = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_InventoryWidget* InventoryWidget = CreateWidget<UFP_InventoryWidget>(this, Inventory);
	WidgetMap.Add(INVENTORY, InventoryWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_RuneToolTip_BP.FP_RuneToolTip_BP_C'");
	TSubclassOf<UFP_RuneToolTip> RuneToolTip = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_RuneToolTip* RuneToolTipWidget = CreateWidget<UFP_RuneToolTip>(this, RuneToolTip);
	WidgetMap.Add(RUNETOOLTIP, RuneToolTipWidget);

	

	
	WidgetMap[GAMESTART]->AddToViewport();
	WidgetMap[STAGE]->AddToViewport();
	//WidgetMap[INVENTORY]->AddToViewport();
	
	
	
	WidgetMap[GAMESTART]->SetVisibility(ESlateVisibility::Visible);
	WidgetMap[STAGE]->SetVisibility(ESlateVisibility::Hidden);
	

	/*WidgetMap[STATUS]->SetRenderTranslation(FVector2D(300.f, 500.f));
	WidgetMap[SKILLUI]->SetRenderTranslation(FVector2D(300.f, 500.f));*/




}

void AFP_PlayerController::ToggleMainUI()
{
	if (WidgetMap[MAINUI]->IsValidLowLevel() == false)
	{
		FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_MainUI.FP_MainUI_C'");
		TSubclassOf<UFP_MainUI> MainUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
		UFP_MainUI* MainUIWidget = CreateWidget<UFP_MainUI>(this, MainUI);
		WidgetMap.Add(MAINUI, MainUIWidget);
	}



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
