// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_StageWidget.h"
#include "Engine.h"
#include "FP_Player.h"
#include "FP_MonsterMgr.h"
#include "FP_PlayerController.h"
#include "FP_InventoryWidget.h"
#include "Button.h"
#include "FP_MainUI.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"


bool UFP_StageWidget::Initialize()
{
	Super::Initialize();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("MainUI"));
	Button->OnClicked.AddDynamic(this, &UFP_StageWidget::Button_MainUI);

	Button = (UButton*)GetWidgetFromName(TEXT("Exit"));
	Button->OnClicked.AddDynamic(this, &UFP_StageWidget::Button_Exit);

	CountText = (UTextBlock*)GetWidgetFromName(TEXT("Count"));

	return true;
}


void UFP_StageWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player != nullptr)
	{
		FString LevelOff = TEXT("LV : ");
		FString fLevel = LevelOff + FString::FromInt(Player->Level.Level);
		LevelText = FText::FromString(fLevel);
		Progress = Player->Level.Exp / Player->Level.FullExp;

		FString StageOff = TEXT("Stage : ");
		
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFP_MonsterMgr::StaticClass(), FoundActors);
		
		FString fStage = StageOff + FString::FromInt(Cast<AFP_MonsterMgr>(FoundActors[0])->Stage);
		StageText = FText::FromString(fStage);

		FString Gem = TEXT("Gem : ") + FString::FromInt(Player->Gem);
		GemText = FText::FromString(Gem);

		PlayerHP = Player->Status.Hp / Player->Status.MaxHp;
		FString PlayerHPTextString = FString::FromInt(Player->Status.Hp) + TEXT(" / ") + FString::FromInt(Player->Status.MaxHp);
		PlayerHPText = FText::FromString(PlayerHPTextString);


		FString SkillTextStr = TEXT("Skill : ");
		if (AFP_Weapon::ActiveSkill == AFP_Weapon::FIREBALL)
			SkillTextStr += TEXT("FireBall");
		else if (AFP_Weapon::ActiveSkill == AFP_Weapon::FIREBLAST)
			SkillTextStr += TEXT("FireBlast");
		else if (AFP_Weapon::ActiveSkill == AFP_Weapon::FIREWALL)
			SkillTextStr += TEXT("FireWall");
		else if (AFP_Weapon::ActiveSkill == AFP_Weapon::ICEBALL)
			SkillTextStr += TEXT("IceBall");
		else if (AFP_Weapon::ActiveSkill == AFP_Weapon::ICEBLAST)
			SkillTextStr += TEXT("IceBlast");
		else 
			SkillTextStr += TEXT("IceOrb");

		SkillText = FText::FromString(SkillTextStr);

		//UE_LOG(LogClass, Log, TEXT("%f"), CountTime);

		if (CountTime >= 0.f && CountTime < 6.f)
		{
			CountTime -= DeltaTime;
			CountText->SetVisibility(ESlateVisibility::Visible);
			FText Count = FText::FromString(FString::FromInt(int(CountTime)));
			CountText->SetText(Count);

			Player->Particle->SetVisibility(false);
		}
		else if (CountTime < 0.f)
		{
			CountText->SetVisibility(ESlateVisibility::Hidden);

			APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			Cast<AFP_PlayerController>(Controller)->SetPause(false);

			int NewStage = ((AFP_MonsterMgr::Stage-1) / 10) * 10 + 1;
			int NewKillCnt = (NewStage-1) * 10;

			AFP_MonsterMgr::Stage = NewStage;
			AFP_MonsterMgr::MonsterKillCnt = NewKillCnt;

			Cast<AFP_PlayerController>(Controller)->RestartLevel();

			CountTime = 10.f;
			Player->Particle->SetVisibility(true);
		}
	}
}


void UFP_StageWidget::Button_MainUI()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	PC->ToggleMainUI();

	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	//Player->TimeAcc = 0.f;
}

void UFP_StageWidget::Button_Exit()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);
	Cast<UFP_MainUI>(PC->GetWidgetMap(AFP_PlayerController::MAINUI))->SetMyVisibility(ESlateVisibility::Visible);

	if (PC->GetWidgetMap(AFP_PlayerController::STATUS)->IsValidLowLevel() == true)
	{
		if (PC->GetWidgetMap(AFP_PlayerController::STATUS)->IsInViewport() == true)
		{
			PC->GetWidgetMap(AFP_PlayerController::STATUS)->RemoveFromViewport();
			
		}
	}

	if (PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->IsValidLowLevel() == true)
	{
		if (PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->IsInViewport() == true)
		{
			PC->GetWidgetMap(AFP_PlayerController::SKILLUI)->RemoveFromViewport();
		}
	}

	if (PC->GetWidgetMap(AFP_PlayerController::INVENTORY)->IsValidLowLevel() == true)
	{
		if (PC->GetWidgetMap(AFP_PlayerController::INVENTORY)->IsInViewport() == true)
		{
			Cast<UFP_InventoryWidget>((PC->GetWidgetMap(AFP_PlayerController::INVENTORY)))->Throbber->SetVisibility(ESlateVisibility::Hidden);
			PC->GetWidgetMap(AFP_PlayerController::INVENTORY)->RemoveFromViewport();
		}
	}

	if (PC->GetWidgetMap(AFP_PlayerController::RUNETOOLTIP)->IsValidLowLevel() == true)
	{
		if (PC->GetWidgetMap(AFP_PlayerController::RUNETOOLTIP)->IsInViewport() == true)
		{
			PC->GetWidgetMap(AFP_PlayerController::RUNETOOLTIP)->RemoveFromViewport();
		}
	}
}
