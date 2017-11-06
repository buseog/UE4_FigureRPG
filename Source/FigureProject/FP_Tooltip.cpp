// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_Tooltip.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_MainUI.h"




bool UFP_Tooltip::Initialize()
{
	Super::Initialize();

	return true;
}


void UFP_Tooltip::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	APlayerController* Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AFP_PlayerController* PC = Cast<AFP_PlayerController>(Controller);

	if (PC->bShowMainUI == false)
	{
		RemoveFromViewport();
		Cast<UFP_SkillUI>(PC->GetWidgetMap(AFP_PlayerController::SKILLUI))->isSkillClicked = false;
	}


}