// Fill out your copyright notice in the Description page of Project Settings.

#include "FigureProjectGameModeBase.h"
#include "FP_HUD.h"
#include "FP_PlayerController.h"
#include "FP_MonsterMgr.h"
#include "FP_Weapon.h"

AFigureProjectGameModeBase::AFigureProjectGameModeBase()
{
	//DefaultPawnClass = 
	HUDClass = AFP_HUD::StaticClass();
	PlayerControllerClass = AFP_PlayerController::StaticClass();

}

void AFigureProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->SpawnActor<AFP_MonsterMgr>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
	GetWorld()->SpawnActor<AFP_Weapon>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
}
