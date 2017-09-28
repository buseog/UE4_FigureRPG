// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_PlayerController.h"
#include "FP_StatusWidget.h"
#include "FP_Player.h"



AFP_PlayerController::AFP_PlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bShowStatus = false;
}

void AFP_PlayerController::BeginPlay()
{
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

void AFP_PlayerController::StatusLevelUp(int _Type)
{
	AFP_Player* pPlayer = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (nullptr == pPlayer)
		return;

	pPlayer->StatusLevelUp(_Type);
}