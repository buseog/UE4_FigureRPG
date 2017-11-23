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
#include "FP_ComMessageUI.h"

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

	FName GameStartWidget_Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_GameStart_BP.FP_GameStart_BP_C'");
	TSubclassOf<UFP_GameStart> GameStart = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *GameStartWidget_Path.ToString()));
	UFP_GameStart* GameStartWidget = CreateWidget<UFP_GameStart>(this, GameStart);
	WidgetArray.Add(GameStartWidget);

	FName Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Stage_BP.FP_Stage_BP_C'");
	TSubclassOf<UFP_StageWidget> Widget2 = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_StageWidget* StageWidget = CreateWidget<UFP_StageWidget>(this, Widget2);
	WidgetArray.Add(StageWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_StatusWidget_BP.FP_StatusWidget_BP_C'");
	TSubclassOf<UFP_StatusWidget> Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_StatusWidget* StatusWidget = CreateWidget<UFP_StatusWidget>(this, Widget);
	StatusWidget->SetRenderScale(FVector2D(3.f, 3.f));
	WidgetArray.Add(StatusWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_MainUI.FP_MainUI_C'");
	TSubclassOf<UFP_MainUI> MainUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_MainUI* MainUIWidget = CreateWidget<UFP_MainUI>(this, MainUI);
	WidgetArray.Add(MainUIWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_SkillUI.FP_SkillUI_C'");
	TSubclassOf<UFP_SkillUI> SkillUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_SkillUI* SkillUIWidget = CreateWidget<UFP_SkillUI>(this, SkillUI);
	SkillUIWidget->SetRenderScale(FVector2D(2.f, 2.f));
	WidgetArray.Add(SkillUIWidget);


	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
	TSubclassOf<UFP_Tooltip> SkillToolTip = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_Tooltip* SkillToolTipWidget = CreateWidget<UFP_Tooltip>(this, SkillToolTip);
	SkillToolTipWidget->SetSKillUI(SkillUIWidget);
	SkillToolTipWidget->SetRenderScale(FVector2D(2.f, 2.f));
	WidgetArray.Add(SkillToolTipWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Inventory_BP.FP_Inventory_BP_C'");
	TSubclassOf<UFP_InventoryWidget> Inventory = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_InventoryWidget* InventoryWidget = CreateWidget<UFP_InventoryWidget>(this, Inventory);
	WidgetArray.Add(InventoryWidget);

	Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_RuneToolTip_BP.FP_RuneToolTip_BP_C'");
	TSubclassOf<UFP_RuneToolTip> RuneToolTip = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	UFP_RuneToolTip* RuneToolTipWidget = CreateWidget<UFP_RuneToolTip>(this, RuneToolTip);
	WidgetArray.Add(RuneToolTipWidget);

	
	WidgetArray[STAGE]->AddToViewport();
	WidgetArray[STAGE]->SetVisibility(ESlateVisibility::Hidden);

	if (Load() == false || isRev == true)
	{
		WidgetArray[GAMESTART]->AddToViewport();
		WidgetArray[GAMESTART]->SetVisibility(ESlateVisibility::Visible);
		isRev = false;
	}
	else
		Cast<UFP_GameStart>(WidgetArray[GAMESTART])->StartWithLoad();
		

	//Message Component
	GetWorld()->SpawnActor<AFP_ComMessageUI>(FVector::ZeroVector, FRotator::ZeroRotator);
	
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
	
	if(LoadGameInstance->PlayerType == 0)
		player->MyType = AFP_Player::FIRE;
	else
		player->MyType = AFP_Player::ICE;

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

	if (LoadGameInstance->ActiveSkill == 0)
		AFP_Weapon::ActiveSkill = AFP_Weapon::FIREBALL;
	else if (LoadGameInstance->ActiveSkill == 1)
		AFP_Weapon::ActiveSkill = AFP_Weapon::FIREBLAST;
	else if (LoadGameInstance->ActiveSkill == 2)
		AFP_Weapon::ActiveSkill = AFP_Weapon::FIREWALL;
	else if (LoadGameInstance->ActiveSkill == 3)
		AFP_Weapon::ActiveSkill = AFP_Weapon::ICEBALL;
	else if (LoadGameInstance->ActiveSkill == 4)
		AFP_Weapon::ActiveSkill = AFP_Weapon::ICEBLAST;
	else if (LoadGameInstance->ActiveSkill == 5)
		AFP_Weapon::ActiveSkill = AFP_Weapon::ICEORB;

	//TArray<AActor*> FoundActor;
	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_MonsterMgr::StaticClass(), FoundActor);
	//if (FoundActor.Num() == 0)
	//	return;

	//Cast<AFP_MonsterMgr>(FoundActor[0])->Stage = LoadGameInstance->Stage;
	AFP_MonsterMgr::MonsterKillCnt = LoadGameInstance->MonsterKillCnt;
	AFP_MonsterMgr::Stage = LoadGameInstance->Stage;

	for (int i = 0; i < LoadGameInstance->Inventory.Num(); ++i)
	{
		AFP_Rune* rune = GetWorld()->SpawnActor<AFP_Rune>(FVector::ZeroVector, FRotator::ZeroRotator);

		AFP_Rune::RuneStat stat;
		stat.Damage = LoadGameInstance->Inventory[i].Damage;
		stat.Speed = LoadGameInstance->Inventory[i].Speed;
		stat.CoolTimeRatio = LoadGameInstance->Inventory[i].CoolTimeRatio;
		stat.Range = LoadGameInstance->Inventory[i].Range;
		
		AFP_Rune::DebuffStat ignite;
		ignite.Damage = LoadGameInstance->Inventory[i].IgniteDamage;
		ignite.Duration = LoadGameInstance->Inventory[i].IgniteDuration;

		AFP_Rune::DebuffStat slow;
		slow.Damage = LoadGameInstance->Inventory[i].SlowDamage;
		slow.Duration = LoadGameInstance->Inventory[i].SlowDuration;

		AFP_Rune::DebuffStat Frozen;
		Frozen.Probability = LoadGameInstance->Inventory[i].FreezeProbability;
		Frozen.Duration = LoadGameInstance->Inventory[i].FreezeDuration;

		rune->ExpBonus = LoadGameInstance->Inventory[i].ExpBonus;
			
		if (stat.Range == 0)
			UE_LOG(LogClass, Log, TEXT("BUG"));

		stat.Tier = LoadGameInstance->Inventory[i].Tier;
		
		for (int j = 0; j < LoadGameInstance->Inventory[i].Type.Num(); ++j)
		{
			switch (LoadGameInstance->Inventory[i].Type[j])
			{
			case 0:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::STAT);
				break;
			case 1:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::PROBABILITY);
				break;
			case 2:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::FIXED);
				break;
			case 3:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::PROJECTILE);
				break;
			case 4:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::AOE);
				break;
			case 5:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::DOT);
				break;
			case 6:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::EXP);
				break;
			case 7:
				stat.Type.Add(LoadGameInstance->Inventory[i].Name, AFP_Rune::TYPE::ETC);
				break;
			}
		}

		TArray<FString> option;
		option.Add(LoadGameInstance->Inventory[i].Option1);
		option.Add(LoadGameInstance->Inventory[i].Option2);
		option.Add(LoadGameInstance->Inventory[i].Option3);

		TArray<float> optionVal;
		optionVal.Add(LoadGameInstance->Inventory[i].OptionVal1);
		optionVal.Add(LoadGameInstance->Inventory[i].OptionVal2);
		optionVal.Add(LoadGameInstance->Inventory[i].OptionVal3);

		rune->Initiate(LoadGameInstance->Inventory[i].Color, LoadGameInstance->Inventory[i].Property, stat, ignite, slow,Frozen, LoadGameInstance->Inventory[i].Name, option, optionVal);

		//½Â·ÄÃß°¡
		if (isRev == false)
		{
			rune->bEquiped = LoadGameInstance->Inventory[i].bEquiped;
			rune->iSkillIndex = LoadGameInstance->Inventory[i].SkillIndex;
			rune->iSocketIndex = LoadGameInstance->Inventory[i].SocketIndex;

			if (rune->bEquiped == true)
			{
				if (rune->iSkillIndex == 0)
					LoadRuneInfoIntoSocket<AFP_FireBall>(rune->iSocketIndex, rune);
				else if (rune->iSkillIndex == 1)
					LoadRuneInfoIntoSocket<AFP_FireBlast>(rune->iSocketIndex, rune);
				else if (rune->iSkillIndex == 2)
					LoadRuneInfoIntoSocket<AFP_FireWall>(rune->iSocketIndex, rune);
				else if (rune->iSkillIndex == 3)
					LoadRuneInfoIntoSocket<AFP_IceBall>(rune->iSocketIndex, rune);
				else if (rune->iSkillIndex == 4)
					LoadRuneInfoIntoSocket<AFP_IceBlast>(rune->iSocketIndex, rune);
				else if (rune->iSkillIndex == 5)
					LoadRuneInfoIntoSocket<AFP_IceOrb>(rune->iSocketIndex, rune);
			}
		}
		///////////////////
		

		player->Inventory.Add(rune);
	}

	return true;
}

void AFP_PlayerController::ToggleMainUI()
{
	if (nullptr == WidgetArray[MAINUI])
		return;

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	UFP_MainUI* MainUI = Cast<UFP_MainUI>(GetWidgetMap(MAINUI));
	if (MainUI == nullptr)
		return;
	
	if (bShowMainUI)
	{
		bShowMainUI = false;
		MainUI->eState = UFP_MainUI::END;

		PC->SetPause(false);
		
	}
	else
	{
		if (MainUI->IsInViewport() == true)
			return;

		bShowMainUI = true;
		MainUI->TimeAcc = 0.f;
		MainUI->eState = UFP_MainUI::START;
		MainUI->AddToViewport();

		PC->SetPause(true);
	}
}

void AFP_PlayerController::SetVisibility(eWIDGET _WidgetNum, bool _isvisible)
{
	if(_isvisible == true)
		WidgetArray[_WidgetNum]->SetVisibility(ESlateVisibility::Visible);
	else
		WidgetArray[_WidgetNum]->SetVisibility(ESlateVisibility::Hidden);
}

UUserWidget* AFP_PlayerController::GetWidgetMap(eWIDGET _key)
{
	if (WidgetArray[_key]->IsValidLowLevel() == false)
	{
		FName Path;
		if (_key == STATUS)
		{
			Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_StatusWidget_BP.FP_StatusWidget_BP_C'");
			TSubclassOf<UFP_StatusWidget> Widget = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
			UFP_StatusWidget* StatusWidget = CreateWidget<UFP_StatusWidget>(this, Widget);
			StatusWidget->SetRenderScale(FVector2D(3.f, 3.f));
			WidgetArray[_key] = StatusWidget;
		}
		else if (_key == MAINUI)
		{
			Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_MainUI.FP_MainUI_C'");
			TSubclassOf<UFP_MainUI> MainUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
			UFP_MainUI* MainUIWidget = CreateWidget<UFP_MainUI>(this, MainUI);
			WidgetArray[_key] = MainUIWidget;
		}
		else if (_key == SKILLUI)
		{
			Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_SkillUI.FP_SkillUI_C'");
			TSubclassOf<UFP_SkillUI> SkillUI = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
			UFP_SkillUI* SkillUIWidget = CreateWidget<UFP_SkillUI>(this, SkillUI);
			SkillUIWidget->SetRenderScale(FVector2D(2.f, 2.f));
			WidgetArray[_key] = SkillUIWidget;
		}
		else if (_key == SKILLTOOLTIP)
		{
			Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_ToolTip_BP.FP_ToolTip_BP_C'");
			TSubclassOf<UFP_Tooltip> SkillToolTip = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
			UFP_Tooltip* SkillToolTipWidget = CreateWidget<UFP_Tooltip>(this, SkillToolTip);
			SkillToolTipWidget->SetSKillUI(Cast<UFP_SkillUI>(GetWidgetMap(SKILLUI)));
			SkillToolTipWidget->SetRenderScale(FVector2D(2.f, 2.f));
			WidgetArray[_key] = SkillToolTipWidget;
		}
		else if (_key == INVENTORY)
		{
			Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_Inventory_BP.FP_Inventory_BP_C'");
			TSubclassOf<UFP_InventoryWidget> Inventory = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
			UFP_InventoryWidget* InventoryWidget = CreateWidget<UFP_InventoryWidget>(this, Inventory);
			WidgetArray[_key] = InventoryWidget;
		}
		else if (_key == RUNETOOLTIP)
		{
			Path = TEXT("WidgetBlueprint'/Game/WidgetBP/FP_RuneToolTip_BP.FP_RuneToolTip_BP_C'");
			TSubclassOf<UFP_RuneToolTip> RuneToolTip = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
			UFP_RuneToolTip* RuneToolTipWidget = CreateWidget<UFP_RuneToolTip>(this, RuneToolTip);
			WidgetArray[_key] = RuneToolTipWidget;
		}
	}

	return WidgetArray[_key];
}

template<typename T>
void AFP_PlayerController::LoadRuneInfoIntoSocket(int _socketIndex, class AFP_Rune* _rune)
{
	UClass* Class = T::StaticClass();
	T* SkillCDO = Class->GetDefaultObject<T>();

	AFP_Skill::Socket Socket;
	for (int i = 0; i < _socketIndex + 1; ++i)
	{
		if(SkillCDO->Sockets.IsValidIndex(i) == false)
			SkillCDO->Sockets.Add(Socket);
	}
		
	
		

	SkillCDO->Sockets[_socketIndex].Rune = _rune;
	SkillCDO->Sockets[_socketIndex].Color = _rune->Color;

}