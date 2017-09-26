// Fill out your copyright notice in the Description page of Project Settings.

#include "MagicianGameModeBase.h"
#include "MagicianPawn.h"
#include "MyPlayerController.h"
#include "MyHUD.h"
#include "MonsterCreator.h"

AMagicianGameModeBase::AMagicianGameModeBase()
{
	DefaultPawnClass = AMagicianPawn::StaticClass();
	PlayerControllerClass = AMyPlayerController::StaticClass();
	HUDClass = AMyHUD::StaticClass();

}

void AMagicianGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<AMonsterCreator>(FVector(0.f, 0.f, 0.f), FRotator(0.f, 0.f, 0.f));
}
