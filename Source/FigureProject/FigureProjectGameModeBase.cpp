// Fill out your copyright notice in the Description page of Project Settings.

#include "FigureProjectGameModeBase.h"
#include "FP_HUD.h"
#include "FP_PlayerController.h"
#include "FP_MonsterMgr.h"
#include "FP_Weapon.h"
#include "FP_Player.h"
#include "FP_ProximityWeapon.h"


AFigureProjectGameModeBase::AFigureProjectGameModeBase()
{

	/*FName Path = TEXT("Blueprint'/Game/FP_Player_BP.FP_Player_BP_C'");
	UClass* PlayerBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));
	DefaultPawnClass = PlayerBP;*/

	DefaultPawnClass = AFP_Player::StaticClass();

	HUDClass = AFP_HUD::StaticClass();
	PlayerControllerClass = AFP_PlayerController::StaticClass();

}

void AFigureProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
}
