// Fill out your copyright notice in the Description page of Project Settings.

#include "FigureProjectGameModeBase.h"
#include "FP_HUD.h"
#include "FP_PlayerController.h"

AFigureProjectGameModeBase::AFigureProjectGameModeBase()
{
	//DefaultPawnClass = 
	HUDClass = AFP_HUD::StaticClass();
	PlayerControllerClass = AFP_PlayerController::StaticClass();

}
