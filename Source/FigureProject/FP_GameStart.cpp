// Fill out your copyright notice in the Description page of Project Settings.

#include "FP_GameStart.h"
#include "Button.h"
#include "Engine.h"
#include "FP_Weapon.h"
#include "FP_ProximityWeapon.h"
#include "FP_MonsterMgr.h"
#include "FP_PlayerController.h"
#include "FP_Player.h"
#include "FP_StageWidget.h"
#include "FP_StatusWidget.h"

void UFP_GameStart::NativeConstruct()
{
	Super::NativeConstruct();

	UButton* FireButton = (UButton*)GetWidgetFromName(TEXT("Fire"));
	FireButton->OnClicked.AddDynamic(this, &UFP_GameStart::ChooseFire);

	UButton* IceButton = (UButton*)GetWidgetFromName(TEXT("Ice"));
	IceButton->OnClicked.AddDynamic(this, &UFP_GameStart::ChooseIce);
}

void UFP_GameStart::ChooseFire()
{
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	AFP_Weapon* Weapon = GetWorld()->SpawnActor<AFP_Weapon>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	Weapon->SetActiveSkill(AFP_Weapon::FIREBALL);

	AFP_PlayerController* PlayerController = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetVisibility(AFP_PlayerController::GAMESTART, false);
	PlayerController->SetVisibility(AFP_PlayerController::STAGE, true);

	UUserWidget* UserWidget = (PlayerController->GetWidgetMap(AFP_PlayerController::STAGE));
	Cast<UFP_StageWidget>(UserWidget)->StageText = FText::FromString(TEXT("BABO"));


	Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->Particle->SetVisibility(true);


}

void UFP_GameStart::ChooseIce()
{
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	AFP_Weapon* Weapon = GetWorld()->SpawnActor<AFP_Weapon>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	Weapon->SetActiveSkill(AFP_Weapon::ICEORB);

	AFP_PlayerController* PlayerController = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetVisibility(AFP_PlayerController::GAMESTART, false);
	PlayerController->SetVisibility(AFP_PlayerController::STAGE, true);

	UUserWidget* UserWidget = (PlayerController->GetWidgetMap(AFP_PlayerController::STAGE));
	Cast<UFP_StageWidget>(UserWidget)->StageText = FText::FromString(TEXT("BABO"));


	Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->Particle->SetVisibility(true);
}