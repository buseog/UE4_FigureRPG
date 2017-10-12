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
	FName Path = TEXT("Blueprint'/Game/FP_Player_BP.FP_Player_BP_C'");
	UClass* PlayerBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));

	DefaultPawnClass = PlayerBP;
	HUDClass = AFP_HUD::StaticClass();
	PlayerControllerClass = AFP_PlayerController::StaticClass();

}

void AFigureProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	//GetWorld()->SpawnActor<AFP_Weapon>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));

	FName Path = TEXT("Blueprint'/Game/FP_ProximityWeapon_BP.FP_ProximityWeapon_BP_C'");
	UClass* WeaponBP = Cast<UClass>(StaticLoadObject(UClass::StaticClass(), NULL, *Path.ToString()));	
	GetWorld()->SpawnActor<AFP_ProximityWeapon>(WeaponBP);
}
