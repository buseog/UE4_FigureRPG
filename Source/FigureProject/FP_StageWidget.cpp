// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_StageWidget.h"
#include "Engine.h"
#include "FP_Player.h"
#include "FP_MonsterMgr.h"
#include "Button.h"


bool UFP_StageWidget::Initialize()
{
	Super::Initialize();

	UButton* Button = (UButton*)GetWidgetFromName(TEXT("MainUI"));
	Button->OnClicked.AddDynamic(this, &UFP_StageWidget::Button_MainUI);

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
	}
}


void UFP_StageWidget::Button_MainUI()
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	PC->ToggleMainUI();
}