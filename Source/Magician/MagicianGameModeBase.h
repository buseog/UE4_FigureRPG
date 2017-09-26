// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Core.h"
#include "Engine.h"
#include "GameFramework/GameModeBase.h"
#include "MagicianGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAGICIAN_API AMagicianGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMagicianGameModeBase();
	
	
	virtual void BeginPlay() override;

};
