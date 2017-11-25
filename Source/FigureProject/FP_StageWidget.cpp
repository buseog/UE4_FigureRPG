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
#include "FP_FireMeteor.h"
#include "FP_GlacialSpike.h"


bool UFP_StageWidget::Initialize()
{
	Super::Initialize();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("MainUI"));
	Button->OnClicked.AddDynamic(this, &UFP_StageWidget::Button_MainUI);

	Button = (UButton*)GetWidgetFromName(TEXT("Exit"));
	Button->OnClicked.AddDynamic(this, &UFP_StageWidget::Button_Exit);

	Button = (UButton*)GetWidgetFromName(TEXT("Ultimate1"));
	Button->OnClicked.AddDynamic(this, &UFP_StageWidget::Button_Ultimate1);

	CountText = (UTextBlock*)GetWidgetFromName(TEXT("Count"));
	UltText = (UTextBlock*)GetWidgetFromName(TEXT("Ult"));

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

		Ultimate1Gage = Player->KillCountForUltimate / 25.f;
		


		if(Player->KillCountForUltimate >= 25)
			GetWidgetFromName(TEXT("Ultimate1"))->SetVisibility(ESlateVisibility::Visible);
		else
			GetWidgetFromName(TEXT("Ultimate1"))->SetVisibility(ESlateVisibility::Hidden);

		if (Player->MyType == AFP_Player::FIRE)
		{
			FName Path = TEXT("Texture2D'/Game/Icon/MeteorIcon.MeteorIcon'");
			UTexture2D* FireIcon = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path.ToString()));
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Normal.ImageSize = FVector2D(90.f, 80.f);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Normal.Margin = 0;
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Normal.SetResourceObject(FireIcon);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Hovered.ImageSize = FVector2D(90.f, 80.f);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Hovered.Margin = 0;
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Hovered.SetResourceObject(FireIcon);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Pressed.ImageSize = FVector2D(90.f, 80.f);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Pressed.Margin = 0;
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Pressed.SetResourceObject(FireIcon);
			UltText->SetText(FText::FromString("Meteor"));
		}
		else
		{
			FName Path = TEXT("Texture2D'/Game/Icon/GlacialSpikeIcon.GlacialSpikeIcon'");
			UTexture2D* IceIcon = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *Path.ToString()));
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Normal.ImageSize = FVector2D(90.f, 80.f);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Normal.Margin = 0;
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Normal.SetResourceObject(IceIcon);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Hovered.ImageSize = FVector2D(90.f, 80.f);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Hovered.Margin = 0;
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Hovered.SetResourceObject(IceIcon);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Pressed.ImageSize = FVector2D(90.f, 80.f);
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Pressed.Margin = 0;
			Cast<UButton>(GetWidgetFromName(TEXT("Ultimate1")))->WidgetStyle.Pressed.SetResourceObject(IceIcon);
			UltText->SetText(FText::FromString("GlacialSpike"));
		}
	}
}


void UFP_StageWidget::Button_MainUI()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	if (CountTime >= 0.f && CountTime < 6.f)
		return;

	PC->ToggleMainUI();
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

void UFP_StageWidget::Button_Ultimate1()
{
	AFP_Player* Player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	AFP_Skill* skill;

	if (Player->MyType == AFP_Player::FIRE)
		skill = GetWorld()->SpawnActor<AFP_FireMeteor>(FVector::ZeroVector, FRotator(180.f, 0.f, 0.f));
	else
		skill = GetWorld()->SpawnActor<AFP_GlacialSpike>(FVector::ZeroVector, FRotator(180.f, 0.f, 0.f));

	Player->KillCountForUltimate = 0;
}