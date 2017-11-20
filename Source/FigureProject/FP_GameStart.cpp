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
#include "CircularThrobber.h"
#include "FP_SkillUI.h"

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


	AFP_Player* player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	player->Particle->SetVisibility(true);

	FVector color = FVector(1.f, 0.f, 0.f);
	player->Particle->SetVectorParameter(TEXT("Color"), color);
	player->Particle->EmitterInstances[4]->bEnabled = false;

	player->SkillLv.FireBall = 1;
	player->InitSkillLv.FireBall = 1;
	player->MyType = AFP_Player::FIRE;

}

void UFP_GameStart::ChooseIce()
{
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	AFP_Weapon* Weapon = GetWorld()->SpawnActor<AFP_Weapon>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	Weapon->SetActiveSkill(AFP_Weapon::ICEBALL);

	AFP_PlayerController* PlayerController = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetVisibility(AFP_PlayerController::GAMESTART, false);
	PlayerController->SetVisibility(AFP_PlayerController::STAGE, true);


	AFP_Player* player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	player->Particle->SetVisibility(true);

	FVector color = FVector(0.f, 0.f, 1.f);
	player->Particle->SetVectorParameter(TEXT("Color"), color);
	player->Particle->EmitterInstances[4]->bEnabled = false;

	player->Particle->SetVisibility(true);
	player->SkillLv.IceBall = 1;
	player->InitSkillLv.IceBall = 1;
	player->MyType = AFP_Player::ICE;

}

void UFP_GameStart::StartWithLoad()
{
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	AFP_Weapon* Weapon = GetWorld()->SpawnActor<AFP_Weapon>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	AFP_PlayerController* PlayerController = Cast<AFP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	PlayerController->SetVisibility(AFP_PlayerController::STAGE, true);

	AFP_Player* player = Cast<AFP_Player>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	player->Particle->SetVisibility(true);

	if (player->MyType == AFP_Player::FIRE)
	{
		FVector color = FVector(1.f, 0.f, 0.f);
		player->Particle->SetVectorParameter(TEXT("Color"), color);
		player->Particle->EmitterInstances[4]->bEnabled = false;
	}
	else
	{
		FVector color = FVector(0.f, 0.f, 1.f);
		player->Particle->SetVectorParameter(TEXT("Color"), color);
		player->Particle->EmitterInstances[4]->bEnabled = false;
	}
}