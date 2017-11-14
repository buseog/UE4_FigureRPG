// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_PlayerController.h"
#include "Engine.h"
#include "FP_StatusWidget.h"
#include "FP_Player.h"
#include "FP_StageWidget.h"
#include "FP_GameStart.h"
#include "FP_MainUI.h"
#include "FP_SkillUI.h"
#include "FP_Tooltip.h"
#include "FP_InventoryWidget.h"
#include "FP_RuneToolTip.h"
#include "FP_SaveGame.h"
#include "FP_MonsterMgr.h"
#include "FP_FireBall.h"
#include "FP_IceBall.h"
#include "FP_IceBlast.h"
#include "FP_IceOrb.h"
#include "FP_FireBlastSpawnPoint.h"
#include "FP_FireBlast.h"
#include "FP_FireWall.h"


bool AFP_PlayerController::isRev = false;
bool AFP_PlayerController::isDead = false;
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

	
	WidgetMap[STAGE]->AddToViewport();
	WidgetMap[STAGE]->SetVisibility(ESlateVisibility::Hidden);

	if (Load() == false || isRev == true)
	{
		WidgetMap[GAMESTART]->AddToViewport();
		WidgetMap[GAMESTART]->SetVisibility(ESlateVisibility::Visible);
		isRev = false;
	}
	else
		Cast<UFP_GameStart>(WidgetMap[GAMESTART])->StartWithLoad();
		
	
	
	
}

bool AFP_PlayerController::Load()
{
	UFP_SaveGame* LoadGameInstance = Cast<UFP_SaveGame>(UGameplayStatics::CreateSaveGameObject(UFP_SaveGame::StaticClass()));
	LoadGameInstance = Cast<UFP_SaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->UserIndex));
	if (LoadGameInstance == nullptr)
		return false;
	
	//TSubclassOf<AFP_Player> Player = AFP_Player::StaticClass();
	//AFP_Player* Player_CDO = Player->GetDefaultObject<AFP_Player>();
	AFP_Player* player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	player->Status.MaxHp = LoadGameInstance->MaxHp;
	player->Status.Hp = LoadGameInstance->Hp;
	player->Status.Attack = LoadGameInstance->Attack;
	player->Status.AttackRange = LoadGameInstance->AttackRange;
	player->Status.AttackSpeed = LoadGameInstance->AttackSpeed;
	player->Status.BulletSpeed = LoadGameInstance->BulletSpeed;

	//////////
	player->SkillLv.FireBall = LoadGameInstance->FireBall;
	player->SkillLv.FireBlast = LoadGameInstance->FireBlast;
	player->SkillLv.FireWall = LoadGameInstance->FireWall;
	player->SkillLv.IceBall = LoadGameInstance->IceBall;
	player->SkillLv.IceBlast = LoadGameInstance->IceBlast;
	player->SkillLv.IceOrb = LoadGameInstance->IceOrb;
	player->SkillLv.SkillPoint = LoadGameInstance->SkillPoint;

	SetSkillDetail<AFP_FireBall>(player->SkillLv.FireBall);
	SetSkillDetail<AFP_FireBlast>(player->SkillLv.FireBlast);
	SetSkillDetail<AFP_FireWall>(player->SkillLv.FireWall);
	SetSkillDetail<AFP_IceBall>(player->SkillLv.IceBall);
	SetSkillDetail<AFP_IceBlast>(player->SkillLv.IceBlast);
	SetSkillDetail<AFP_IceOrb>(player->SkillLv.IceOrb);

	player->Level.Level = LoadGameInstance->Level;
	player->Level.Exp = LoadGameInstance->Exp;
	player->Level.FullExp = LoadGameInstance->FullExp;
	player->Level.Point = LoadGameInstance->Point;

	player->Gem = LoadGameInstance->Gem;


	//TArray<AActor*> FoundActor;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_MonsterMgr::StaticClass(), FoundActor);
	//if (FoundActor.Num() == 0)
	//	return;

	//Cast<AFP_MonsterMgr>(FoundActor[0])->Stage = LoadGameInstance->Stage;
	AFP_MonsterMgr::MonsterKillCnt = LoadGameInstance->MonsterKillCnt;
	AFP_MonsterMgr::Stage = LoadGameInstance->Stage;

	return true;
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

